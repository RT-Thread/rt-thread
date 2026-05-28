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
#define DSI_REG_DPI_LP_CMD_TIM      0x018
#define DSI_REG_PCKHDL_CFG          0x02c
#define DSI_REG_GEN_VCID            0x030
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
#define DSI_REG_HS_RD_TO_CNT        0x080
#define DSI_REG_BTA_TO_CNT          0x08c
#define DSI_REG_LPCLK_CTRL          0x094
#define DSI_REG_PHY_TMR_LPCLK_CFG   0x098
#define DSI_REG_PHY_TMR_CFG         0x09c
#define DSI_REG_PHY_TMR_RD_CFG      0x0f4
#define DSI_REG_PHY_IF_CFG          0x0a4
#define DSI_REG_PHY_RSTZ            0x0a0
#define DSI_REG_PHY_STATUS          0x0b0
#define DSI_REG_PHY_TST_CTRL0       0x0b4
#define DSI_REG_PHY_TST_CTRL1       0x0b8
#define DSI_REG_INT_ST0             0x0bc
#define DSI_REG_INT_ST1             0x0c0
#define DSI_REG_INT_MSK0            0x0c4
#define DSI_REG_INT_MSK1            0x0c8
#define DSI_REG_MODE_CFG            0x034

#define DSI_CMD_MODE_ALL_LP         0x010f7f00U
#define DSI_DPI_COLOR_RGB565        0x1U
#define DSI_DPI_BYTES_PER_PIXEL     2U

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

struct dsi_dphy_timing {
    k_u32 lane_mbps;
    k_u16 clk_lp2hs;
    k_u16 clk_hs2lp;
    k_u16 data_lp2hs;
    k_u16 data_hs2lp;
};

static const k_u32 minimum_lbccs[] = {10U, 5U, 4U, 3U};

static const struct dsi_dphy_timing dphy_timings[] = {
    {  80U,  21U,  17U,  15U,  10U},
    {  90U,  23U,  17U,  16U,  10U},
    { 100U,  22U,  17U,  16U,  10U},
    { 110U,  25U,  18U,  17U,  11U},
    { 120U,  26U,  20U,  18U,  11U},
    { 130U,  27U,  19U,  19U,  11U},
    { 140U,  27U,  19U,  19U,  11U},
    { 150U,  28U,  20U,  20U,  12U},
    { 160U,  30U,  21U,  22U,  13U},
    { 170U,  30U,  21U,  23U,  13U},
    { 180U,  31U,  21U,  23U,  13U},
    { 190U,  32U,  22U,  24U,  13U},
    { 205U,  35U,  22U,  25U,  13U},
    { 220U,  37U,  26U,  27U,  15U},
    { 235U,  38U,  28U,  27U,  16U},
    { 250U,  41U,  29U,  30U,  17U},
    { 275U,  43U,  29U,  32U,  18U},
    { 300U,  45U,  32U,  35U,  19U},
    { 325U,  48U,  33U,  36U,  18U},
    { 350U,  51U,  35U,  40U,  20U},
    { 400U,  59U,  37U,  44U,  21U},
    { 450U,  65U,  40U,  49U,  23U},
    { 500U,  71U,  41U,  54U,  24U},
    { 550U,  77U,  44U,  57U,  26U},
    { 600U,  82U,  46U,  64U,  27U},
    { 650U,  87U,  48U,  67U,  28U},
    { 700U,  94U,  52U,  71U,  29U},
    { 750U,  99U,  52U,  75U,  31U},
    { 800U, 105U,  55U,  82U,  32U},
    { 850U, 110U,  58U,  85U,  32U},
    { 900U, 115U,  58U,  88U,  35U},
    { 950U, 120U,  62U,  93U,  36U},
    {1000U, 128U,  63U,  99U,  38U},
    {1050U, 132U,  65U, 102U,  38U},
    {1100U, 138U,  67U, 106U,  39U},
    {1150U, 146U,  69U, 112U,  42U},
    {1200U, 151U,  71U, 117U,  43U},
    {1250U, 153U,  74U, 120U,  45U},
    {1300U, 160U,  73U, 124U,  46U},
    {1350U, 165U,  76U, 130U,  47U},
    {1400U, 172U,  78U, 134U,  49U},
    {1450U, 177U,  80U, 138U,  49U},
    {1500U, 183U,  81U, 143U,  52U},
    {1550U, 191U,  84U, 147U,  52U},
    {1600U, 194U,  85U, 152U,  52U},
    {1650U, 201U,  86U, 155U,  53U},
    {1700U, 208U,  88U, 161U,  53U},
    {1750U, 212U,  89U, 165U,  53U},
    {1800U, 220U,  90U, 171U,  54U},
    {1850U, 223U,  92U, 175U,  54U},
    {1900U, 231U,  91U, 180U,  55U},
    {1950U, 236U,  95U, 185U,  56U},
    {2000U, 243U,  97U, 190U,  56U},
    {2050U, 248U,  99U, 194U,  58U},
    {2100U, 252U, 100U, 199U,  59U},
    {2150U, 259U, 102U, 204U,  61U},
    {2200U, 266U, 105U, 210U,  62U},
    {2250U, 269U, 109U, 213U,  63U},
    {2300U, 272U, 109U, 217U,  65U},
    {2350U, 281U, 112U, 225U,  66U},
    {2400U, 283U, 115U, 226U,  66U},
    {2450U, 282U, 115U, 226U,  67U},
    {2500U, 281U, 118U, 227U,  67U},
};

extern void K_LOG(int level, int module, const char *fmt, ...);
extern void *memcpy(void *dst, const void *src, unsigned long count);

static k_u32 curren_video_mode;

static void dsi_video_mode_config(k_u32 mode);

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

static k_u32 dsi_phy_read(k_u32 offset)
{
    uintptr_t base = phy_base_addr();
    k_u32 value = 0;

    if (base != 0U) {
        value = raw_readl((void *)(base + offset));
        DSI_FENCE_IR();
    }

    return value;
}

void dwc_dsi_debug_dump(void)
{
    rt_kprintf("DSI base=%p phy=%p mode=%u\n",
               display_remap ? display_remap->dsi_base : RT_NULL,
               display_remap ? display_remap->phy_base : RT_NULL,
               curren_video_mode);
    rt_kprintf("DSI pwr=0x%08x clk=0x%08x mode=0x%08x vid_mode=0x%08x cmd_mode=0x%08x lpclk=0x%08x dpi_lp=0x%08x dpi_color=0x%08x\n",
               dsi_read(DSI_REG_PWR_UP), dsi_read(DSI_REG_CLKMGR_CFG),
               dsi_read(DSI_REG_MODE_CFG), dsi_read(DSI_REG_VID_MODE_CFG),
               dsi_read(DSI_REG_CMD_MODE_CFG), dsi_read(DSI_REG_LPCLK_CTRL),
               dsi_read(DSI_REG_DPI_LP_CMD_TIM),
               dsi_read(DSI_REG_DPI_COLOR_CODING));
    rt_kprintf("DSI phy_if=0x%08x phy_rstz=0x%08x phy_status=0x%08x hs_rd_to=0x%08x phy_tmr_rd=0x%08x\n",
               dsi_read(DSI_REG_PHY_IF_CFG), dsi_read(DSI_REG_PHY_RSTZ),
               dsi_read(DSI_REG_PHY_STATUS), dsi_read(DSI_REG_HS_RD_TO_CNT),
               dsi_read(DSI_REG_PHY_TMR_RD_CFG));
    rt_kprintf("DSI pkt=%u chunks=%u null=%u hsa=%u hbp=%u hline=%u vsa=%u vbp=%u vfp=%u vact=%u\n",
               dsi_read(DSI_REG_VID_PKT_SIZE), dsi_read(DSI_REG_VID_NUM_CHUNKS),
               dsi_read(DSI_REG_VID_NULL_SIZE), dsi_read(DSI_REG_VID_HSA_TIME),
               dsi_read(DSI_REG_VID_HBP_TIME), dsi_read(DSI_REG_VID_HLINE_TIME),
               dsi_read(DSI_REG_VID_VSA_LINES), dsi_read(DSI_REG_VID_VBP_LINES),
               dsi_read(DSI_REG_VID_VFP_LINES), dsi_read(DSI_REG_VID_VACTIVE_LINES));
    rt_kprintf("DSI status=0x%08x msk0=0x%08x msk1=0x%08x\n",
               dsi_read(DSI_REG_CMD_PKT_STATUS),
               dsi_read(DSI_REG_INT_MSK0), dsi_read(DSI_REG_INT_MSK1));
    rt_kprintf("DSI_PHY 0x00=0x%08x 0x04=0x%08x 0x08=0x%08x 0x0c=0x%08x 0x10=0x%08x 0x14=0x%08x 0x18=0x%08x\n",
               dsi_phy_read(0x00), dsi_phy_read(0x04), dsi_phy_read(0x08),
               dsi_phy_read(0x0c), dsi_phy_read(0x10), dsi_phy_read(0x14),
               dsi_phy_read(0x18));
}

void dwc_dsi_set_dpi_color_coding(k_u32 coding)
{
    dsi_write(coding & 0x7U, DSI_REG_DPI_COLOR_CODING);
}

void dwc_dsi_set_video_scan(k_u32 dpi_color, k_u32 pkt_size,
                            k_u32 hsa, k_u32 hbp, k_u32 hline,
                            k_u32 video_mode)
{
    dsi_write(0, DSI_REG_PWR_UP);
    dsi_write(dpi_color & 0x7U, DSI_REG_DPI_COLOR_CODING);
    dsi_write(pkt_size & 0x3fffU, DSI_REG_VID_PKT_SIZE);
    dsi_write(hsa, DSI_REG_VID_HSA_TIME);
    dsi_write(hbp, DSI_REG_VID_HBP_TIME);
    dsi_write(hline, DSI_REG_VID_HLINE_TIME);
    curren_video_mode = video_mode;
    dsi_write(0, DSI_REG_MODE_CFG);
    dsi_video_mode_config(video_mode);
    dsi_write(1, DSI_REG_LPCLK_CTRL);
    dsi_write(1, DSI_REG_PWR_UP);
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

static void dsi_dump_packet_error(k_u8 type, k_u32 header, k_u32 status)
{
    K_LOG(3, KD_DSI_MODULE_ID,
          "%s: packet 0x%x timeout, header 0x%x status 0x%x\n",
          __func__, type, header, status);
    rt_kprintf("DSI packet error: type=0x%02x header=0x%08x status=0x%08x\n",
               type, header, status);
    rt_kprintf("DSI packet regs: pwr=0x%08x mode=0x%08x cmd=0x%08x vid=0x%08x lpclk=0x%08x dpi_lp=0x%08x phy_rstz=0x%08x phy_status=0x%08x\n",
               dsi_read(DSI_REG_PWR_UP), dsi_read(DSI_REG_MODE_CFG),
               dsi_read(DSI_REG_CMD_MODE_CFG), dsi_read(DSI_REG_VID_MODE_CFG),
               dsi_read(DSI_REG_LPCLK_CTRL), dsi_read(DSI_REG_DPI_LP_CMD_TIM),
               dsi_read(DSI_REG_PHY_RSTZ), dsi_read(DSI_REG_PHY_STATUS));
    rt_kprintf("DSI packet ints: int0=0x%08x int1=0x%08x msk0=0x%08x msk1=0x%08x\n",
               dsi_read(DSI_REG_INT_ST0), dsi_read(DSI_REG_INT_ST1),
               dsi_read(DSI_REG_INT_MSK0), dsi_read(DSI_REG_INT_MSK1));
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

static void dsi_message_config(uint8_t channel, uint8_t lp, uint8_t ack)
{
    k_u32 value = 0;
    k_u32 video_mode;

    (void)channel;

    dsi_write(0x00100004U, DSI_REG_DPI_LP_CMD_TIM);

    if (ack != 0U) {
        value |= 0x2U;
    }
    if (lp != 0U) {
        value |= DSI_CMD_MODE_ALL_LP;
    }

    dsi_write(value, DSI_REG_CMD_MODE_CFG);

    video_mode = dsi_read(DSI_REG_VID_MODE_CFG);
    if (lp != 0U) {
        video_mode |= 0x00008000U;
    } else {
        video_mode &= ~0x00008000U;
    }
    dsi_write(video_mode, DSI_REG_VID_MODE_CFG);
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
        dsi_write(DSI_CMD_MODE_ALL_LP, DSI_REG_CMD_MODE_CFG);
        dsi_write(0, DSI_REG_VID_MODE_CFG);
    } else {
        dsi_write(0, DSI_REG_MODE_CFG);
        dsi_video_mode_config(video_mode);
    }
    dsi_write(1, DSI_REG_LPCLK_CTRL);
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

void k230_dsi_phy_pll_config(uint32_t m, uint32_t n, uint8_t voc)
{
    phy_update_bits(0x10, 0x00000200U, 0x00000200U);
    phy_update_bits(0x10, 0x00000200U, 0);
    phy_update_bits(0x10, 0x00000003U, 0x00000001U);
    phy_update_bits(0x08, 0x07fe0000U, (n & 0x3ffU) << 17);
    phy_update_bits(0x08, 0x78000000U, (m & 0x0fU) << 27);
    phy_update_bits(0x10, 0x0001f800U, ((k_u32)voc & 0x3fU) << 11);
    phy_update_bits(0x08, 0x0000007fU, 0x00000010U);
    phy_update_bits(0x08, 0x00000300U, 0);
    phy_update_bits(0x08, 0x0001f800U, 0);
    phy_update_bits(0x10, 0x000001f8U, 0x00000040U);

    k230_dsi_write_phy_reg(0x14, 0x02);
    k230_dsi_write_phy_reg(0x15, 0x60);
    k230_dsi_write_phy_reg(0x16, 0x03);
    k230_dsi_write_phy_reg(0x1d, 0x01);

    phy_update_bits(0x10, 0x00000400U, 0x00000400U);
    rt_thread_mdelay(1);
    phy_update_bits(0x10, 0x00000400U, 0);
}

void k230_dsi_phy0_config(uint32_t m, uint32_t n, uint8_t voc, uint8_t hs_freq)
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
    k230_dsi_write_phy_reg(0x44, hs_freq);
    k230_dsi_write_phy_reg(0xa0, 0x40);
    k230_dsi_write_phy_reg(0xa4, 0x11);
    k230_dsi_write_phy_reg(0xa4, 0x85);
    k230_dsi_write_phy_reg(0xa3, 0x01);
    k230_dsi_write_phy_reg(0x1f, 0x01);
    k230_dsi_write_phy_reg(0x4a, 0x40);

    phy_update_bits(0x00, 0x00003f3cU, 0x000028a0U);
    k230_dsi_phy_pll_config(m, n, voc);

    if (base != 0U) {
        DSI_FENCE_WO();
        raw_writel(0x28a0U, (void *)base);
    }

    dsi_write(0x0c, DSI_REG_PHY_RSTZ);
}

void k230_dsi_phy1_config(uint8_t hs_freq)
{
    uintptr_t base = phy_base_addr();
    int retry = 10;

    if (base != 0U) {
        DSI_FENCE_WO();
        raw_writel(0x00400000U, (void *)(base + 0x04));
    }

    dsi_write(1, DSI_REG_PHY_TST_CTRL0);
    rt_thread_mdelay(1);
    dsi_write(0, DSI_REG_PHY_TST_CTRL0);
    k230_dsi_write_phy_reg(0x0c, 0);
    k230_dsi_write_phy_reg(0x44, hs_freq);
    k230_dsi_write_phy_reg(0x30, 0xff);
    k230_dsi_write_phy_reg(0xa0, 0x40);
    k230_dsi_write_phy_reg(0xa4, 0x11);
    k230_dsi_write_phy_reg(0xa4, 0x85);
    k230_dsi_write_phy_reg(0xa3, 0x01);
    k230_dsi_write_phy_reg(0x1f, 0x01);
    k230_dsi_write_phy_reg(0x4a, 0x40);

    if (base != 0U) {
        k_u32 value = raw_readl((void *)base);

        DSI_FENCE_IR();
        value &= ~0x000000fcU;
        value |= 0x000000a0U;
        value &= ~0x00003f00U;
        value |= 0x00002800U;
        DSI_FENCE_WO();
        raw_writel(value, (void *)base);
    }

    dsi_write(4, DSI_REG_PHY_RSTZ);
    dsi_write(0x0d, DSI_REG_PHY_RSTZ);
    dsi_write(0x0f, DSI_REG_PHY_RSTZ);
    k230_dsi_write_phy_reg(0x03, 0x80);

    do {
        if (dsi_read(DSI_REG_PHY_TST_CTRL1) == 0x580U) {
            return;
        }
        k230_dsi_write_phy_reg(0x03, 0x80);
        rt_thread_mdelay(1);
    } while (--retry > 0);

    K_LOG(7, KD_DSI_MODULE_ID, "%s: test interface ready status 0x%x\n",
          __func__, dsi_read(DSI_REG_PHY_TST_CTRL1));
}

static k_u32 dsi_phy_stopstate_mask(k_u32 lane_num)
{
    k_u32 mask = 0x0dU;

    for (k_u32 i = 0; i < lane_num; i++) {
        if (i == 0U) {
            mask |= 0x30U;
        } else if (i == 1U) {
            mask |= 0x180U;
        } else if (i == 2U) {
            mask |= 0x600U;
        } else if (i == 3U) {
            mask |= 0x1800U;
        }
    }

    return mask;
}

static void dsi_wait_phy_status(k_u32 mask, const char *stage)
{
    k_u32 status = 0;

    for (k_u32 timeout = 50000U; timeout != 0U; timeout -= DSI_WAIT_US) {
        status = dsi_read(DSI_REG_PHY_STATUS);
        if ((status & mask) == mask) {
            return;
        }
        rt_hw_us_delay(DSI_WAIT_US);
    }

    K_LOG(3, KD_DSI_MODULE_ID, "%s: %s timeout, status 0x%x mask 0x%x\n",
          __func__, stage, status, mask);
}

void k230_dsi_phy_config(k_u32 lane_sel, k_u32 m, k_u32 n, k_u8 voc,
                         k_u8 hs_freq)
{
    uintptr_t base = phy_base_addr();
    k_u32 mask = dsi_phy_stopstate_mask(lane_sel);

    k230_dsi_phy0_config(m, n, voc, hs_freq);
    k230_dsi_phy1_config(hs_freq);

    if (base != 0U) {
        DSI_FENCE_WO();
        raw_writel(0, (void *)(base + 0x04));
    }

    dsi_write(0x0d, DSI_REG_PHY_RSTZ);
    dsi_write(0x0f, DSI_REG_PHY_RSTZ);
    dsi_wait_phy_status(mask, "stop-state");
    rt_thread_mdelay(1);

    if (base != 0U) {
        DSI_FENCE_WO();
        raw_writel(0x00400000U, (void *)(base + 0x04));
    }

    dsi_wait_phy_status(mask, "external stop-state");
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
        dsi_dump_packet_error(type, header, dsi_read(DSI_REG_CMD_PKT_STATUS));
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

static k_u32 dsi_get_minimum_lbcc(k_u32 lane_count)
{
    if (lane_count == 0U || lane_count > 4U) {
        return minimum_lbccs[0];
    }

    return minimum_lbccs[lane_count - 1U];
}

static k_u32 dsi_get_hcomponent_lbcc(const k_vo_dsi_config *config,
                                     k_u32 component)
{
    uint64_t lbcc;
    uint64_t rem;
    k_u32 lane_count = dsi_lane_count(config->lanes);
    k_u32 minimum;

    if (config->video_mode == K_BURST_MODE) {
        lbcc = ((uint64_t)component * (uint64_t)(config->phy.datarate / 1000U)) >> 3;
    } else {
        lbcc = ((uint64_t)component * (uint64_t)config->timing->pclk_khz *
                DSI_DPI_BYTES_PER_PIXEL) /
               (uint64_t)(lane_count * 8U);
    }

    rem = lbcc % (uint64_t)config->timing->pclk_khz;
    lbcc = lbcc / (uint64_t)config->timing->pclk_khz;
    if (rem != 0U) {
        lbcc++;
    }

    minimum = dsi_get_minimum_lbcc(lane_count);
    if (lbcc < minimum) {
        lbcc = minimum;
    }

    return (k_u32)lbcc;
}

static int dsi_get_phy_timings(k_u32 lane_mbps, struct dsi_dphy_timing *timing)
{
    k_u32 best_delta = 0xffffffffU;
    int best = -1;

    for (k_u32 i = 0; i < sizeof(dphy_timings) / sizeof(dphy_timings[0]); i++) {
        k_u32 table_mbps = dphy_timings[i].lane_mbps;
        k_u32 delta = table_mbps > lane_mbps ? table_mbps - lane_mbps :
                                                lane_mbps - table_mbps;

        if (delta < best_delta) {
            best_delta = delta;
            best = (int)i;
        }
    }

    if (best < 0) {
        return -1;
    }

    *timing = dphy_timings[best];
    return 0;
}

static void dsi_wait_phy_bit(k_u32 bit, const char *stage)
{
    k_u32 status = 0;

    for (k_u32 timeout = 10000U; timeout != 0U; timeout -= DSI_WAIT_US) {
        status = dsi_read(DSI_REG_PHY_STATUS);
        if ((status & bit) != 0U) {
            return;
        }
        rt_hw_us_delay(DSI_WAIT_US);
    }

    K_LOG(3, KD_DSI_MODULE_ID, "%s: %s timeout, status 0x%x\n",
          __func__, stage, status);
}

void dwc_dsi_init(k_vo_dsi_config *config)
{
    struct kd_dsi_resolution res;
    struct dsi_dphy_timing phy_timing;
    k_u32 lane_num;
    k_u32 lane_mbps;
    k_u32 byte_clk;
    k_u32 lane_byte_mbps;
    k_u32 tx_escape_clk_division;
    k_u32 timeout_clock_division;
    k_u32 hline_pixels;
    k_u32 hsa_lbcc;
    k_u32 hbp_lbcc;
    k_u32 hline_lbcc;
    k_u32 phy_tmr_cfg;
    k_u32 phy_tmr_lpclk_cfg;

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

    lane_mbps = config->phy.datarate / 1000000U;
    lane_byte_mbps = lane_mbps / 8U;
    byte_clk = lane_byte_mbps;
    if (byte_clk == 0U) {
        byte_clk = 1U;
    }

    tx_escape_clk_division = (lane_byte_mbps + (config->lp_speed_mhz == 0U ? 20U : config->lp_speed_mhz) - 1U) /
                             (config->lp_speed_mhz == 0U ? 20U : config->lp_speed_mhz);
    if (tx_escape_clk_division == 0U) {
        tx_escape_clk_division = 1U;
    }
    if (tx_escape_clk_division > 255U) {
        tx_escape_clk_division = 255U;
    }

    timeout_clock_division = (lane_byte_mbps + 1U - 1U) / 1U;
    if (timeout_clock_division == 0U) {
        timeout_clock_division = 1U;
    }
    if (timeout_clock_division > 255U) {
        timeout_clock_division = 255U;
    }

    if (tx_escape_clk_division < 1U || tx_escape_clk_division > 20U) {
        K_LOG(4, KD_DSI_MODULE_ID,
              "%s: unusual escape clock divider %u for lane_mbps=%u\n",
              __func__, tx_escape_clk_division, lane_mbps);
    }

    if (dsi_get_phy_timings(lane_mbps, &phy_timing) != 0) {
        phy_timing.clk_lp2hs = 0x73U;
        phy_timing.clk_hs2lp = 0x3aU;
        phy_timing.data_lp2hs = 0xceU;
        phy_timing.data_hs2lp = 0x23U;
        K_LOG(4, KD_DSI_MODULE_ID,
              "%s: using default dphy timings for lane_mbps=%u\n",
              __func__, lane_mbps);
    }
    phy_timing.data_lp2hs += phy_timing.clk_lp2hs;
    phy_tmr_cfg = (((k_u32)phy_timing.data_hs2lp & 0x3ffU) << 16) |
                  ((k_u32)phy_timing.data_lp2hs & 0x3ffU);
    phy_tmr_lpclk_cfg = (((k_u32)phy_timing.clk_hs2lp & 0x3ffU) << 16) |
                        ((k_u32)phy_timing.clk_lp2hs & 0x3ffU);

    hline_pixels = res.hdisplay + res.hsync_len + res.hback_porch + res.hfront_porch;
    hsa_lbcc = dsi_get_hcomponent_lbcc(config, res.hsync_len);
    hbp_lbcc = dsi_get_hcomponent_lbcc(config, res.hback_porch);
    hline_lbcc = dsi_get_hcomponent_lbcc(config, hline_pixels);

    curren_video_mode = config->video_mode;

    dsi_write(0, DSI_REG_PWR_UP);
    dsi_write(((timeout_clock_division & 0xffU) << 8) |
              (tx_escape_clk_division & 0xffU),
              DSI_REG_CLKMGR_CFG);
    dsi_write(config->vc_id & 0x3U, DSI_REG_DPI_VCID);
    dsi_write((config->vc_id & 0x3U) | ((config->vc_id & 0x3U) << 8),
              DSI_REG_GEN_VCID);
    dsi_write(DSI_DPI_COLOR_RGB565, DSI_REG_DPI_COLOR_CODING);
    dsi_write(0, DSI_REG_DPI_CFG_POL);
    dsi_write(0x1cU, DSI_REG_PCKHDL_CFG);
    dsi_video_mode_config(config->video_mode);

    dsi_write(res.hdisplay & 0x3fffU, DSI_REG_VID_PKT_SIZE);
    dsi_write(0, DSI_REG_VID_NUM_CHUNKS);
    dsi_write(0, DSI_REG_VID_NULL_SIZE);

    dsi_write(0x1388U, DSI_REG_TO_CNT_CFG);
    dsi_write(0x0d00U, DSI_REG_BTA_TO_CNT);
    dsi_write(0x1388U, DSI_REG_HS_RD_TO_CNT);
    dsi_write(1, DSI_REG_MODE_CFG);
    dsi_write(hsa_lbcc, DSI_REG_VID_HSA_TIME);
    dsi_write(hbp_lbcc, DSI_REG_VID_HBP_TIME);
    dsi_write(hline_lbcc, DSI_REG_VID_HLINE_TIME);
    dsi_write(res.vsync_len, DSI_REG_VID_VSA_LINES);
    dsi_write(res.vback_porch, DSI_REG_VID_VBP_LINES);
    dsi_write(res.vfront_porch, DSI_REG_VID_VFP_LINES);
    dsi_write(res.vdisplay, DSI_REG_VID_VACTIVE_LINES);
    dsi_write(0, DSI_REG_PHY_RSTZ);
    dsi_write(0, DSI_REG_PHY_TST_CTRL0);
    dsi_write(1, DSI_REG_PHY_TST_CTRL0);
    dsi_write(0, DSI_REG_PHY_TST_CTRL0);
    dsi_write(phy_tmr_cfg, DSI_REG_PHY_TMR_CFG);
    dsi_write(0x2710U, DSI_REG_PHY_TMR_RD_CFG);
    dsi_write(phy_tmr_lpclk_cfg, DSI_REG_PHY_TMR_LPCLK_CFG);
    dsi_write(0x2800U | ((lane_num - 1U) & 0x3U), DSI_REG_PHY_IF_CFG);
    dsi_read(DSI_REG_INT_ST0);
    dsi_read(DSI_REG_INT_ST1);
    dsi_write(0xffffffffU, DSI_REG_INT_MSK0);
    dsi_write(0xffffffffU, DSI_REG_INT_MSK1);

    k230_dsi_phy_config((k_u32)config->lanes, config->phy.m, config->phy.n,
                        (uint8_t)config->phy.voc,
                        (uint8_t)config->phy.hs_freq);

    dsi_write(0x0f, DSI_REG_PHY_RSTZ);

    dsi_wait_phy_bit(0x1U, "phy lock");
    dsi_wait_phy_bit(0x4U, "clk lane stop-state");

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
