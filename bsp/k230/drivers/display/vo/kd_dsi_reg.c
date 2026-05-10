#include "kd_dsi_reg.h"
#include "vo_display_remap.h"

#include <rtthread.h>

#include <stddef.h>
#include <stdint.h>

#define KD_DSI_MODULE_ID               11

#define DSI_REG_PWR_UP              0x004
#define DSI_REG_CLKMGR_CFG          0x008
#define DSI_REG_DPI_VCID            0x00c
#define DSI_REG_DPI_COLOR_CODING    0x010
#define DSI_REG_DPI_CFG_POL         0x014
#define DSI_REG_VID_MODE_CFG        0x038
#define DSI_REG_VID_PKT_SIZE        0x03c
#define DSI_REG_VID_NUM_CHUNKS      0x040
#define DSI_REG_VID_NULL_SIZE       0x044
#define DSI_REG_VID_HSA_TIME        0x048
#define DSI_REG_VID_HBP_TIME        0x04c
#define DSI_REG_VID_HLINE_TIME      0x050
#define DSI_REG_VID_VSA_LINES       0x054
#define DSI_REG_VID_VBP_LINES       0x058
#define DSI_REG_VID_VFP_LINES       0x05c
#define DSI_REG_VID_VACTIVE_LINES   0x060
#define DSI_REG_CMD_MODE_CFG        0x068
#define DSI_REG_GEN_HDR             0x06c
#define DSI_REG_GEN_PLD_DATA        0x070
#define DSI_REG_CMD_PKT_STATUS      0x074
#define DSI_REG_TO_CNT_CFG          0x078
#define DSI_REG_BTA_TO_CNT          0x08c
#define DSI_REG_PHY_TMR_CFG         0x098
#define DSI_REG_PHY_TMR_LPCLK_CFG   0x09c
#define DSI_REG_PHY_IF_CFG          0x0a4
#define DSI_REG_PHY_RSTZ            0x0a0
#define DSI_REG_PHY_STATUS          0x0b0
#define DSI_REG_PHY_TST_CTRL0       0x0b4
#define DSI_REG_PHY_TST_CTRL1       0x0b8
#define DSI_REG_INT_ST0             0x0bc
#define DSI_REG_INT_ST1             0x0c0
#define DSI_REG_INT_MSK0            0x0c4
#define DSI_REG_INT_MSK1            0x0c8
#define DSI_REG_MODE_CFG            0x094

#define DSI_PACKET_DCS_SHORT_WRITE0 0x05
#define DSI_PACKET_DCS_SHORT_WRITE1 0x15
#define DSI_PACKET_DCS_LONG_WRITE   0x39
#define DSI_PACKET_DCS_READ         0x06
#define DSI_PACKET_GEN_SHORT_WRITE0 0x03
#define DSI_PACKET_GEN_SHORT_WRITE1 0x13
#define DSI_PACKET_GEN_SHORT_WRITE2 0x23
#define DSI_PACKET_GEN_LONG_WRITE   0x29
#define DSI_PACKET_GEN_READ0        0x04
#define DSI_PACKET_GEN_READ1        0x14
#define DSI_PACKET_GEN_READ2        0x24

#define DSI_WAIT_US                 10
#define DSI_WAIT_RETRY              20000U

#if defined(__riscv)
#define DSI_FENCE_WO() __asm__ volatile("fence w,o" ::: "memory")
#define DSI_FENCE_IR() __asm__ volatile("fence i,r" ::: "memory")
#else
#define DSI_FENCE_WO() __asm__ volatile("" ::: "memory")
#define DSI_FENCE_IR() __asm__ volatile("" ::: "memory")
#endif

struct kd_dsi_resolution {
    k_u32 pclk;
    k_u32 phyclk;
    k_u32 htotal;
    k_u32 hdisplay;
    k_u32 hsync_len;
    k_u32 hback_porch;
    k_u32 hfront_porch;
    k_u32 vtotal;
    k_u32 vdisplay;
    k_u32 vsync_len;
    k_u32 vback_porch;
    k_u32 vfront_porch;
};

struct kd_dsi_config {
    k_u32 pclk;
    k_u32 phyclk;
    k_u32 n;
    k_u32 m;
    k_u32 voc;
    k_u32 lane_num;
    k_u32 hs_freq;
    k_u32 cmd_mode;
    k_u32 work_mode;
    k_u32 video_mode;
    struct kd_dsi_resolution *resolution;
    uint8_t color_coding;
    uint8_t lp_div;
};

extern void K_LOG(int level, int module, const char *fmt, ...);
extern void *memcpy(void *dst, const void *src, unsigned long count);

static k_u32 curren_video_mode;

static k_u32 dsi_lane_count(k_vo_dsi_lane_num lanes)
{
    switch (lanes) {
    case K_DSI_1LAN:
        return 1;
    case K_DSI_2LAN:
        return 2;
    case K_DSI_4LAN:
        return 4;
    default:
        return 0;
    }
}

static inline void raw_writel(k_u32 value, volatile void *addr)
{
    *(volatile k_u32 *)addr = value;
}

static inline k_u32 raw_readl(const volatile void *addr)
{
    return *(const volatile k_u32 *)addr;
}

static uintptr_t dsi_base_addr(void)
{
    if (display_remap == NULL || display_remap->dsi_base == NULL) {
        (void)vo_display_remap_init();
    }
    if (display_remap == NULL || display_remap->dsi_base == NULL) {
        return 0;
    }
    return (uintptr_t)display_remap->dsi_base;
}

static uintptr_t phy_base_addr(void)
{
    if (display_remap == NULL || display_remap->phy_base == NULL) {
        (void)vo_display_remap_init();
    }
    if (display_remap == NULL || display_remap->phy_base == NULL) {
        return 0;
    }
    return (uintptr_t)display_remap->phy_base;
}

static void dsi_write(k_u32 value, k_u32 offset)
{
    uintptr_t base = dsi_base_addr();

    K_LOG(7, KD_DSI_MODULE_ID,
          "[Func]:%s [Line]:%d [Info]:DSI write: offset 0x%x, val 0x%x\n",
          __func__, 160, offset, value);

    if (base == 0U) {
        return;
    }

    DSI_FENCE_WO();
    raw_writel(value, (void *)(base + offset));
}

static k_u32 dsi_read(k_u32 offset)
{
    uintptr_t base = dsi_base_addr();
    k_u32 value = 0;

    if (base != 0U) {
        value = raw_readl((void *)(base + offset));
        DSI_FENCE_IR();
    }

    K_LOG(7, KD_DSI_MODULE_ID,
          "[Func]:%s [Line]:%d [Info]:DSI read: offset 0x%x, val 0x%x\n",
          __func__, 179, offset, value);
    return value;
}

static void phy_update_bits(k_u32 offset, k_u32 mask, k_u32 value)
{
    uintptr_t base = phy_base_addr();
    k_u32 reg;

    if (base == 0U) {
        return;
    }

    reg = raw_readl((void *)(base + offset));
    DSI_FENCE_IR();
    reg &= ~mask;
    reg |= value & mask;
    DSI_FENCE_WO();
    raw_writel(reg, (void *)(base + offset));
}

static int packet_format_is_long(uint8_t type)
{
    return type == DSI_PACKET_DCS_LONG_WRITE ||
           type == DSI_PACKET_GEN_LONG_WRITE;
}

static uint8_t dcs_packet_type(uint32_t len)
{
    if (len == 1U) {
        return DSI_PACKET_DCS_SHORT_WRITE0;
    }
    if (len == 2U) {
        return DSI_PACKET_DCS_SHORT_WRITE1;
    }
    return DSI_PACKET_DCS_LONG_WRITE;
}

static int wait_status_clear(k_u32 mask)
{
    unsigned int retry;

    for (retry = 0; retry < DSI_WAIT_RETRY; ++retry) {
        if ((dsi_read(DSI_REG_CMD_PKT_STATUS) & mask) == 0U) {
            return 0;
        }
        rt_hw_us_delay(DSI_WAIT_US);
    }

    return -1;
}

static int wait_status_set(k_u32 mask)
{
    unsigned int retry;

    for (retry = 0; retry < DSI_WAIT_RETRY; ++retry) {
        if ((dsi_read(DSI_REG_CMD_PKT_STATUS) & mask) == mask) {
            return 0;
        }
        rt_hw_us_delay(DSI_WAIT_US);
    }

    return -1;
}

static int write_payload(const uint8_t *payload, uint32_t len)
{
    uint32_t offset = 0;

    while (offset < len) {
        uint32_t word = 0;
        uint32_t chunk = len - offset;
        uint32_t i;

        if (wait_status_clear(0x8U) != 0) {
            return -1;
        }

        if (chunk > 4U) {
            chunk = 4U;
        }

        for (i = 0; i < chunk; ++i) {
            word |= (k_u32)payload[offset + i] << (i * 8U);
        }

        dsi_write(word, DSI_REG_GEN_PLD_DATA);
        offset += chunk;
    }

    return 0;
}

static int read_payload(uint8_t *data, uint32_t len)
{
    uint32_t offset = 0;

    while (offset < len) {
        k_u32 word;
        uint32_t chunk = len - offset;

        if (wait_status_clear(0x10U) != 0) {
            return offset == 0U ? -1 : (int)offset;
        }

        if (chunk > 4U) {
            chunk = 4U;
        }

        word = dsi_read(DSI_REG_GEN_PLD_DATA);
        memcpy(data + offset, &word, chunk);
        offset += chunk;

        if ((dsi_read(DSI_REG_CMD_PKT_STATUS) & 0x10U) != 0U) {
            break;
        }
    }

    return (int)offset;
}

static void dsi_message_config(uint8_t channel, uint8_t ack, uint8_t lp)
{
    k_u32 value = 0;

    if (ack != 0U) {
        value |= 0x1U;
    }
    if (lp != 0U) {
        value |= 0x70fU;
    }
    value |= ((k_u32)channel & 0x3U) << 8;

    dsi_write(value, DSI_REG_CMD_MODE_CFG);
}

static void dsi_video_mode_config(k_u32 mode)
{
    k_u32 value = 0xbf00U;

    if (mode == 1U) {
        value |= 0x1U;
    } else if (mode != 2U) {
        value |= 0x2U;
    }

    dsi_write(value, DSI_REG_VID_MODE_CFG);
}

static void dsi_set_mode(uint8_t enable, k_u32 video_mode)
{
    dsi_write(0, DSI_REG_PWR_UP);
    if (enable == 0U) {
        dsi_write(1, DSI_REG_MODE_CFG);
        dsi_write(0x010f7f00U, DSI_REG_CMD_MODE_CFG);
        dsi_write(0, DSI_REG_VID_MODE_CFG);
    } else {
        dsi_write(0, DSI_REG_MODE_CFG);
        dsi_video_mode_config(video_mode);
    }
    dsi_write(1, DSI_REG_MODE_CFG);
    dsi_write(1, DSI_REG_PWR_UP);
}

static void wait_for_two_frames(const struct kd_dsi_resolution *res)
{
    k_u32 htotal;
    k_u32 vtotal;
    k_u32 frame_ms;

    if (res == NULL || res->pclk == 0U) {
        rt_thread_mdelay(34);
        return;
    }

    htotal = res->hdisplay + res->hsync_len + res->hback_porch + res->hfront_porch;
    vtotal = res->vdisplay + res->vsync_len + res->vback_porch + res->vfront_porch;
    frame_ms = (k_u32)(((uint64_t)htotal * (uint64_t)vtotal) / (uint64_t)res->pclk);
    rt_thread_mdelay((int)((frame_ms + 1U) * 2U));
}

void k230_dsi_write_phy_reg(uint8_t addr, uint8_t value)
{
    dsi_write(0x10000U | addr, DSI_REG_PHY_TST_CTRL1);
    dsi_write(2, DSI_REG_PHY_TST_CTRL0);
    dsi_write(0, DSI_REG_PHY_TST_CTRL0);
    dsi_write(value, DSI_REG_PHY_TST_CTRL1);
    dsi_write(2, DSI_REG_PHY_TST_CTRL0);
    dsi_write(0, DSI_REG_PHY_TST_CTRL0);
}

void k230_dsi_phy_pll_config(uint32_t n, uint32_t m, uint8_t hs_freq)
{
    phy_update_bits(0x10, 0x00000200U, 0x00000200U);
    phy_update_bits(0x10, 0x00000200U, 0);
    phy_update_bits(0x10, 0x00000003U, 0x00000001U);
    phy_update_bits(0x08, 0x07fe0000U, (n & 0x3ffU) << 17);
    phy_update_bits(0x08, 0x78000000U, (m & 0x0fU) << 27);
    phy_update_bits(0x10, 0x0001f800U, ((k_u32)hs_freq & 0x3fU) << 11);

    k230_dsi_write_phy_reg(0x14, 0x02);
    k230_dsi_write_phy_reg(0x15, 0x60);
    k230_dsi_write_phy_reg(0x16, 0x03);
    k230_dsi_write_phy_reg(0x1d, 0x01);

    phy_update_bits(0x10, 0x00000400U, 0x00000400U);
    rt_thread_mdelay(1);
    phy_update_bits(0x10, 0x00000400U, 0);
}

void k230_dsi_phy0_config(uint32_t n, uint32_t m, uint8_t hs_freq, uint8_t lane_num)
{
    uintptr_t base = phy_base_addr();

    if (base != 0U) {
        DSI_FENCE_WO();
        raw_writel(0, (void *)(base + 0x04));
    }

    dsi_write(0x0c, DSI_REG_PHY_RSTZ);
    dsi_write(1, DSI_REG_PHY_TST_CTRL0);
    dsi_write(0, DSI_REG_PHY_TST_CTRL0);

    k230_dsi_write_phy_reg(0x0c, 0x03);
    k230_dsi_write_phy_reg(0x44, lane_num);
    k230_dsi_write_phy_reg(0xa0, 0x40);
    k230_dsi_write_phy_reg(0xa4, 0x11);
    k230_dsi_write_phy_reg(0xa4, 0x85);
    k230_dsi_write_phy_reg(0xa3, 0x01);
    k230_dsi_write_phy_reg(0x1f, 0x01);
    k230_dsi_write_phy_reg(0x4a, 0x40);

    phy_update_bits(0x00, 0x00003f3cU, 0x000028a0U);
    k230_dsi_phy_pll_config(n, m, hs_freq);

    if (base != 0U) {
        DSI_FENCE_WO();
        raw_writel(0x28a0U, (void *)base);
    }

    dsi_write(0x0c, DSI_REG_PHY_RSTZ);
}

void k230_dsi_phy1_config(uint8_t lane_num)
{
    uintptr_t base = phy_base_addr();

    if (base != 0U) {
        DSI_FENCE_WO();
        raw_writel(0x00400000U, (void *)(base + 0x04));
    }

    dsi_write(1, DSI_REG_PHY_TST_CTRL0);
    rt_thread_mdelay(1);
    dsi_write(0, DSI_REG_PHY_TST_CTRL0);
    k230_dsi_write_phy_reg(0x0c, 0);
    k230_dsi_write_phy_reg(0x44, lane_num);
}

int dwc_dsi_send_packet(k_u8 type, k_u8 channel, const void *payload,
                        uint32_t payload_len, uint8_t read)
{
    const uint8_t *bytes = (const uint8_t *)payload;
    k_u32 header;

    if (payload_len != 0U && bytes == NULL) {
        return -1;
    }

    dsi_message_config(channel, 1, read);
    if (wait_status_clear(0x2U) != 0) {
        return -1;
    }

    if (packet_format_is_long(type)) {
        if (write_payload(bytes, payload_len) != 0) {
            return -1;
        }
        header = ((k_u32)type | (((k_u32)channel & 0x3U) << 6)) |
                 (payload_len << 8);
    } else {
        k_u32 data0 = payload_len > 0U ? bytes[0] : 0U;
        k_u32 data1 = payload_len > 1U ? bytes[1] : 0U;

        header = ((k_u32)type | (((k_u32)channel & 0x3U) << 6)) |
                 (data0 << 8) | (data1 << 16);
    }

    dsi_write(header, DSI_REG_GEN_HDR);

    if (wait_status_set(0x5U) != 0) {
        K_LOG(3, KD_DSI_MODULE_ID, "%s: packet 0x%x timeout, status 0x%x\n",
              __func__, type, dsi_read(DSI_REG_CMD_PKT_STATUS));
        return -1;
    }

    return 0;
}

int dwc_dsi_dcs_write(const void *data, uint32_t len, uint8_t channel)
{
    return dwc_dsi_send_packet(dcs_packet_type(len), channel, data, len, 0);
}

int dwc_dsi_dcs_read(uint8_t cmd, void *data, uint32_t len, uint8_t channel)
{
    int ret;

    if (len != 0U && data == NULL) {
        return -1;
    }

    ret = dwc_dsi_send_packet(DSI_PACKET_DCS_READ, channel, &cmd, 1, 1);
    if (ret != 0) {
        return ret;
    }
    if (wait_status_clear(0x20U) != 0) {
        return -1;
    }

    return read_payload((uint8_t *)data, len);
}

int dwc_dsi_generic_write(const void *data, uint32_t len, uint8_t channel)
{
    uint8_t type;

    if (len == 0U) {
        type = DSI_PACKET_GEN_SHORT_WRITE0;
    } else if (len == 1U) {
        type = DSI_PACKET_GEN_SHORT_WRITE1;
    } else if (len == 2U) {
        type = DSI_PACKET_GEN_SHORT_WRITE2;
    } else {
        type = DSI_PACKET_GEN_LONG_WRITE;
    }

    return dwc_dsi_send_packet(type, channel, data, len, 0);
}

int dwc_dsi_generic_read(const void *params, uint32_t params_len, void *data,
                         uint32_t len, uint8_t channel)
{
    uint8_t type;
    int ret;

    if ((params_len != 0U && params == NULL) || (len != 0U && data == NULL)) {
        return -1;
    }

    if (params_len == 0U) {
        type = DSI_PACKET_GEN_READ0;
    } else if (params_len == 1U) {
        type = DSI_PACKET_GEN_READ1;
    } else {
        type = DSI_PACKET_GEN_READ2;
    }

    ret = dwc_dsi_send_packet(type, channel, params, params_len, 1);
    if (ret != 0) {
        return ret;
    }
    if (wait_status_clear(0x20U) != 0) {
        return -1;
    }

    return read_payload((uint8_t *)data, len);
}

void dwc_dsi_dump_config(const k_vo_dsi_config *config)
{
    if (config == NULL) {
        rt_kprintf("dwc dsi config is null\n");
        return;
    }

    rt_kprintf("dwc dsi config:\n");
    rt_kprintf("  lane_num %u\n", config->lanes);
    rt_kprintf("  cmd_mode %u\n", config->cmd_mode);
    rt_kprintf("  video_mode %u\n", config->video_mode);
    rt_kprintf("  pclk %u phyclk %u n %u m %u voc %u hs_freq %u\n",
               config->timing->pclk_khz * 1000, config->phy.datarate / 2,
               config->phy.n, config->phy.m, config->phy.voc,
               config->phy.hs_freq);
}

void dwc_dsi_init(k_vo_dsi_config *config)
{
    struct kd_dsi_resolution res;
    k_u32 lane_num;
    k_u32 byte_clk;
    k_u32 tx_escape_clk_division;
    k_u32 hline;

    if (config == NULL || config->timing == NULL) {
        K_LOG(3, KD_DSI_MODULE_ID, "%s: invalid dsi config\n", __func__);
        return;
    }

    rt_memset(&res, 0, sizeof(res));
    res.pclk = config->timing->pclk_khz * 1000;
    res.phyclk = config->phy.datarate / 2;
    res.hdisplay = config->timing->hactive;
    res.hsync_len = config->timing->hsync_len;
    res.hback_porch = config->timing->hback_porch;
    res.hfront_porch = config->timing->hfront_porch;
    res.htotal = res.hdisplay + res.hsync_len + res.hback_porch + res.hfront_porch;
    res.vdisplay = config->timing->vactive;
    res.vsync_len = config->timing->vsync_len;
    res.vback_porch = config->timing->vback_porch;
    res.vfront_porch = config->timing->vfront_porch;
    res.vtotal = res.vdisplay + res.vsync_len + res.vback_porch + res.vfront_porch;

    lane_num = dsi_lane_count(config->lanes);
    if (lane_num == 0U) {
        K_LOG(3, KD_DSI_MODULE_ID, "%s: invalid lane config %u\n",
              __func__, config->lanes);
        return;
    }
    byte_clk = res.phyclk / 8000000U;
    if (byte_clk == 0U) {
        byte_clk = 1U;
    }
    tx_escape_clk_division = byte_clk / (config->lp_speed_mhz == 0U ? 20U : config->lp_speed_mhz);
    if (tx_escape_clk_division == 0U) {
        tx_escape_clk_division = 1U;
    }
    if (tx_escape_clk_division > 255U) {
        tx_escape_clk_division = 255U;
    }

    curren_video_mode = config->video_mode;

    dsi_write(0, DSI_REG_PWR_UP);
    dsi_write(((tx_escape_clk_division & 0xffU) << 8) | (byte_clk & 0xffU),
              DSI_REG_CLKMGR_CFG);
    dsi_write(config->vc_id & 0x3U, DSI_REG_DPI_VCID);
    dsi_write(0x5U, DSI_REG_DPI_COLOR_CODING);
    dsi_write(0, DSI_REG_DPI_CFG_POL);
    dsi_video_mode_config(config->video_mode);

    dsi_write(res.hdisplay & 0x3fffU, DSI_REG_VID_PKT_SIZE);
    dsi_write(0, DSI_REG_VID_NUM_CHUNKS);
    dsi_write(0, DSI_REG_VID_NULL_SIZE);

    hline = res.hdisplay + res.hsync_len + res.hback_porch + res.hfront_porch;
    dsi_write(res.hsync_len, DSI_REG_VID_HSA_TIME);
    dsi_write(res.hback_porch, DSI_REG_VID_HBP_TIME);
    dsi_write(hline, DSI_REG_VID_HLINE_TIME);
    dsi_write(res.vsync_len, DSI_REG_VID_VSA_LINES);
    dsi_write(res.vback_porch, DSI_REG_VID_VBP_LINES);
    dsi_write(res.vfront_porch, DSI_REG_VID_VFP_LINES);
    dsi_write(res.vdisplay, DSI_REG_VID_VACTIVE_LINES);

    dsi_write(0x1388U, DSI_REG_TO_CNT_CFG);
    dsi_write(0x0d00U, DSI_REG_BTA_TO_CNT);
    dsi_write(0x2710U, DSI_REG_PHY_TMR_CFG);
    dsi_write(0x0073003aU, DSI_REG_PHY_TMR_LPCLK_CFG);
    dsi_write(0x2800U | ((lane_num - 1U) & 0x3U), DSI_REG_PHY_IF_CFG);
    dsi_write(0xffffffffU, DSI_REG_INT_MSK0);
    dsi_write(0xffffffffU, DSI_REG_INT_MSK1);

    k230_dsi_phy0_config(config->phy.n, config->phy.m,
                         (uint8_t)config->phy.hs_freq, (uint8_t)lane_num);

    dsi_write(0x0f, DSI_REG_PHY_RSTZ);
    if ((dsi_read(DSI_REG_PHY_STATUS) & 0x1U) == 0U) {
        K_LOG(3, KD_DSI_MODULE_ID, "%s: phy lock timeout\n", __func__);
    }
    if ((dsi_read(DSI_REG_PHY_STATUS) & 0x4U) == 0U) {
        K_LOG(3, KD_DSI_MODULE_ID, "%s: phy stop-state timeout\n", __func__);
    }

    wait_for_two_frames(&res);
    dsi_set_mode(0, 0);
}

int dwc_dsi_enable(void)
{
    dsi_set_mode(1, curren_video_mode);
    return 0;
}

int dwc_dsi_disable(void)
{
    dsi_set_mode(0, 0);
    dsi_write(0, DSI_REG_PWR_UP);
    dsi_write(0, DSI_REG_PHY_RSTZ);
    return 0;
}
