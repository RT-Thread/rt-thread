/* Adapted from atk_k230d connector_bus_dsi.c for RT-Thread BSP */

#include <rtthread.h>
#include <string.h>

#include "connector_panel.h"
#include "connector_bus_dsi.h"

#define DSI_PHY_REF_CLK 24000000

typedef struct {
    k_u64 min_freq;
    k_u64 max_freq;
    k_u8  hsfreqrange;
} dsi_phy_hsfreq_range_t;

static const dsi_phy_hsfreq_range_t hsfreq_ranges[] = {
    { 2363125000ULL, 2500000000ULL, 0x49 }, { 2315625000ULL, 2500000000ULL, 0x48 }, { 2268125000ULL, 2500000000ULL, 0x47 },
    { 2220625000ULL, 2480625000ULL, 0x46 }, { 2173125000ULL, 2428125000ULL, 0x45 }, { 2125625000ULL, 2375625000ULL, 0x44 },
    { 2078125000ULL, 2323125000ULL, 0x43 }, { 2030625000ULL, 2270625000ULL, 0x42 }, { 1983125000ULL, 2218125000ULL, 0x41 },
    { 1935625000ULL, 2165625000ULL, 0x40 }, { 1888125000ULL, 2113125000ULL, 0x0F }, { 1840625000ULL, 2060625000ULL, 0x3F },
    { 1793125000ULL, 2008125000ULL, 0x2F }, { 1745625000ULL, 1955625000ULL, 0x1E }, { 1698125000ULL, 1903125000ULL, 0x0E },
    { 1650625000ULL, 1850625000ULL, 0x3E }, { 1603125000ULL, 1798125000ULL, 0x2E }, { 1555625000ULL, 1745625000ULL, 0x1D },
    { 1508125000ULL, 1693125000ULL, 0x0D }, { 1460625000ULL, 1640625000ULL, 0x3D }, { 1413125000ULL, 1588125000ULL, 0x2C },
    { 1365625000ULL, 1535625000ULL, 0x1C }, { 1318125000ULL, 1483125000ULL, 0x0C }, { 1270625000ULL, 1430625000ULL, 0x3C },
    { 1223125000ULL, 1378125000ULL, 0x2B }, { 1175625000ULL, 1325625000ULL, 0x1B }, { 1128125000ULL, 1273125000ULL, 0x0B },
    { 1080625000ULL, 1220625000ULL, 0x3B }, { 1033125000ULL, 1168125000ULL, 0x2A }, { 985625000ULL, 1115625000ULL, 0x1A },
    { 938125000ULL, 1063125000ULL, 0x0A },  { 890625000ULL, 1010625000ULL, 0x3A },  { 843125000ULL, 958125000ULL, 0x29 },
    { 795625000ULL, 905625000ULL, 0x19 },   { 748125000ULL, 853125000ULL, 0x09 },   { 700625000ULL, 800625000ULL, 0x39 },
    { 653125000ULL, 748125000ULL, 0x28 },   { 605625000ULL, 695625000ULL, 0x18 },   { 558125000ULL, 643125000ULL, 0x07 },
    { 510625000ULL, 590625000ULL, 0x37 },   { 463125000ULL, 538125000ULL, 0x26 },   { 415625000ULL, 485625000ULL, 0x16 },
    { 368125000ULL, 433125000ULL, 0x05 },   { 320625000ULL, 380625000ULL, 0x35 },   { 296875000ULL, 354375000ULL, 0x25 },
    { 273125000ULL, 328125000ULL, 0x14 },   { 249375000ULL, 301875000ULL, 0x04 },   { 225625000ULL, 275625000ULL, 0x33 },
    { 211375000ULL, 259875000ULL, 0x23 },   { 197125000ULL, 244125000ULL, 0x13 },   { 182875000ULL, 228375000ULL, 0x03 },
    { 168625000ULL, 212625000ULL, 0x32 },   { 159125000ULL, 202125000ULL, 0x22 },   { 149625000ULL, 191625000ULL, 0x12 },
    { 140125000ULL, 181125000ULL, 0x02 },   { 130625000ULL, 170625000ULL, 0x31 },   { 121125000ULL, 160125000ULL, 0x21 },
    { 111625000ULL, 149625000ULL, 0x11 },   { 102125000ULL, 139125000ULL, 0x01 },   { 92625000ULL, 128625000ULL, 0x30 },
    { 83125000ULL, 118125000ULL, 0x20 },    { 80000000ULL, 107625000ULL, 0x10 },    { 80000000ULL, 97125000ULL, 0x00 },
};

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

static inline k_u32 dsi_bus_calc_lane_clk(const k_vo_timing* res, k_vo_dsi_lane_num lanes)
{
    k_u32 lane_count = dsi_lane_count(lanes);

    if (!res || res->pclk_khz == 0 || lane_count == 0)
        return 0;

    return ((res->pclk_khz * 3 * 8 * 1000) / (lane_count * 2));
}

static k_u32 dsi_phy_calc_hsfreqrange(k_u64 bitrate_hz)
{
    int num_ranges = sizeof(hsfreq_ranges) / sizeof(hsfreq_ranges[0]);

    for (int i = 0; i < num_ranges; i++) {
        if (bitrate_hz >= hsfreq_ranges[i].min_freq && bitrate_hz <= hsfreq_ranges[i].max_freq) {
            return hsfreq_ranges[i].hsfreqrange;
        }
    }

    rt_kprintf("dsi_phy: unsupported bitrate %llu Hz\n", bitrate_hz);
    return 0;
}

static k_u32 dsi_phy_calc_vco(k_u32 fout_hz)
{
    if (fout_hz >= 1100000000 && fout_hz <= 1250000000) return 0x01;
    if (fout_hz >= 630000000 && fout_hz <= 1149000000)  return 0x03;
    if (fout_hz >= 420000000 && fout_hz <= 660000000)   return 0x07;
    if (fout_hz >= 320000000 && fout_hz <= 440000000)   return 0x0F;
    if (fout_hz >= 210000000 && fout_hz <= 330000000)   return 0x17;
    if (fout_hz >= 160000000 && fout_hz <= 220000000)   return 0x1F;
    if (fout_hz >= 105000000 && fout_hz <= 165000000)   return 0x27;
    if (fout_hz >= 80000000 && fout_hz <= 110000000)    return 0x2F;
    if (fout_hz >= 52500000 && fout_hz <= 82500000)     return 0x37;
    if (fout_hz >= 40000000 && fout_hz <= 55000000)     return 0x3F;

    rt_kprintf("dsi_phy: unsupported VCO frequency %u Hz\n", fout_hz);
    return 0x17;
}

static int dsi_phy_calc_m_and_n_impl(k_u32 fout, k_u32 mut, k_u32 clkin, k_u32* om, k_u32* on)
{
    for (int n = 1; n <= 16; n++) {
        uint64_t numerator = (uint64_t)fout * mut * (n + 1);
        if (numerator % clkin == 0) {
            uint32_t mp2 = numerator / clkin;
            if (mp2 >= 42 && mp2 <= 627) {
                *om = mp2 - 2;
                *on = n;
                return 0;
            }
        }
    }

    rt_kprintf("dsi_phy: can't generate phy attr with configuration\n");
    rt_kprintf("dsi_phy: try to increase or decrease pclk\n");
    return -1;
}

static int dsi_phy_calc_m_and_n(k_u32 fout, k_u32* m, k_u32* n)
{
    k_u32 mut = 1;

    if (fout >= 320000000 && fout <= 1250000000)
        mut = 1;
    else if (fout >= 160000000 && fout <= 320000000)
        mut = 2;
    else if (fout >= 80000000 && fout <= 160000000)
        mut = 4;
    else if (fout >= 40000000 && fout <= 80000000)
        mut = 8;
    else
        rt_kprintf("dsi_phy: unsupported MIPI Phy Clock: %u\n", fout);

    return dsi_phy_calc_m_and_n_impl(fout, mut, DSI_PHY_REF_CLK, m, n);
}

static int dsi_bus_check_lane_clk(k_u32 lane_clk_hz)
{
    k_u32 mut = 1;

    if (lane_clk_hz == 0)
        return -1;

    if (lane_clk_hz >= 320000000 && lane_clk_hz <= 1250000000)
        mut = 1;
    else if (lane_clk_hz >= 160000000 && lane_clk_hz <= 320000000)
        mut = 2;
    else if (lane_clk_hz >= 80000000 && lane_clk_hz <= 160000000)
        mut = 4;
    else if (lane_clk_hz >= 40000000 && lane_clk_hz <= 80000000)
        mut = 8;
    else
        return -1;

    for (int n = 1; n <= 16; n++) {
        uint64_t numerator = (uint64_t)lane_clk_hz * mut * (n + 1);
        if (numerator % DSI_PHY_REF_CLK == 0) {
            uint32_t mp2 = numerator / DSI_PHY_REF_CLK;
            if (mp2 >= 42 && mp2 <= 627)
                return 0;
        }
    }

    return -1;
}

k_u32 dsi_correct_pclk(k_u32 pclk_hz, k_vo_dsi_lane_num lanes)
{
    k_u32 ratio, candidate_pclk, lane_clk, lane_count;
    int delta;

    lane_count = dsi_lane_count(lanes);
    if (pclk_hz == 0 || lane_count == 0)
        return 0;

    ratio = (VO_PIXEL_CLOCK_HZ + pclk_hz / 2) / pclk_hz;
    if (ratio == 0)
        ratio = 1;

    for (delta = 0; delta <= 10; delta++) {
        if (ratio + delta > 0) {
            candidate_pclk = VO_PIXEL_CLOCK_HZ / (ratio + delta);
            lane_clk = (candidate_pclk / 1000 * 3 * 8 * 1000) / (lane_count * 2);
            if (dsi_bus_check_lane_clk(lane_clk) == 0)
                return candidate_pclk;
        }
        if (delta > 0 && ratio > (k_u32)delta) {
            candidate_pclk = VO_PIXEL_CLOCK_HZ / (ratio - delta);
            lane_clk = (candidate_pclk / 1000 * 3 * 8 * 1000) / (lane_count * 2);
            if (dsi_bus_check_lane_clk(lane_clk) == 0)
                return candidate_pclk;
        }
    }

    return 0;
}

static int dsi_bus_calculate_phy_attr(k_u32 lane_clk_hz, k_u32* n, k_u32* m, k_u32* voc, k_u32* hs_freq)
{
    k_u32 m_val, n_val;

    if (!n || !m || !voc || !hs_freq || lane_clk_hz == 0)
        return -1;

    if (dsi_phy_calc_m_and_n(lane_clk_hz, &m_val, &n_val) != 0)
        return -1;

    *m       = m_val;
    *n       = n_val;
    *voc     = dsi_phy_calc_vco(lane_clk_hz);
    *hs_freq = 0x80 | dsi_phy_calc_hsfreqrange(lane_clk_hz * 2);

    return 0;
}

static int dsi_bus_init(const struct panel_desc* desc)
{
    k_u32 lane_clk;
    k_u32 m, n, voc, hs_freq;
    k_vo_dsi_config cfg;

    if (!desc)
        return -1;

    lane_clk = dsi_bus_calc_lane_clk(&desc->timing, desc->bus.dsi.lanes);
    if (lane_clk == 0) {
        rt_kprintf("dsi_bus_init: failed to calculate lane_clk\n");
        return -2;
    }

    if (dsi_bus_calculate_phy_attr(lane_clk, &n, &m, &voc, &hs_freq) != 0) {
        rt_kprintf("dsi_bus_init: failed to calculate phy attr\n");
        return -3;
    }

    cfg.phy.datarate = lane_clk * 2;
    cfg.phy.m        = m;
    cfg.phy.n        = n;
    cfg.phy.voc      = voc;
    cfg.phy.hs_freq  = hs_freq;

    cfg.timing       = &desc->timing;
    cfg.lanes        = desc->bus.dsi.lanes;
    cfg.cmd_mode     = desc->bus.dsi.cmd_mode;
    cfg.video_mode   = desc->bus.dsi.video_mode;
    cfg.vc_id        = desc->bus.dsi.vc_id;
    cfg.lp_speed_mhz = desc->bus.dsi.lp_cmd_speed_mhz;

    dwc_dsi_init(&cfg);

    if (desc->ops && desc->ops->read_chip_id) {
        k_u32 chipid = desc->ops->read_chip_id(desc);
        rt_kprintf("panel %s, chip id: 0x%08x\n", desc->name, chipid);
    }

    return 0;
}

static int dsi_bus_enable(const struct panel_desc* desc)
{
    if (!desc)
        return -1;

    dwc_dsi_enable();
    return 0;
}

k_s32 dsi_send_cmd_sequence(const struct panel_desc* desc, const k_u8* cmd_seq, size_t cmd_size, k_bool dump)
{
    uint32_t               cmd_remain;
    const uint8_t *        pcmd, *pcmd_end;
    k_connector_cmd_slice* cmd;

    if (!cmd_seq || !desc) {
        rt_kprintf("no init sequence set.\n");
        return -1;
    }

    pcmd     = cmd_seq;
    pcmd_end = pcmd + cmd_size;

    do {
        cmd        = (k_connector_cmd_slice*)pcmd;
        cmd_remain = pcmd_end - pcmd;

        if (cmd->cmd_size > (cmd_remain - sizeof(k_connector_cmd_slice))) {
            rt_kprintf("error cmd sequence. %d > %d\n", cmd->cmd_size,
                       cmd_remain - (int)sizeof(k_connector_cmd_slice));
            break;
        }

        if (cmd->cmd_size) {
            if ((DSI_DCS_SHORT_WRITE == cmd->cmd_type) || (DSI_DCS_SHORT_WRITE_PARAM == cmd->cmd_type)
                || (DSI_DCS_LONG_WRITE == cmd->cmd_type)) {

                if (dwc_dsi_dcs_write(cmd->cmd_data, cmd->cmd_size, desc->bus.dsi.vc_id) != 0) {
                    rt_kprintf("dsi send cmd failed, but we treat it as non-fatal\n");
                    return 0;
                }
            } else if ((DSI_GENERIC_SHORT_WRITE_0_PARAM == cmd->cmd_type) || (DSI_GENERIC_SHORT_WRITE_1_PARAM == cmd->cmd_type)
                       || (DSI_GENERIC_SHORT_WRITE_2_PARAM == cmd->cmd_type) || (DSI_GENERIC_LONG_WRITE == cmd->cmd_type)) {

                if (dwc_dsi_generic_write(cmd->cmd_data, cmd->cmd_size, desc->bus.dsi.vc_id) != 0) {
                    rt_kprintf("dsi send cmd failed, but we treat it as non-fatal\n");
                    return 0;
                }
            } else {
                rt_kprintf("unsupport cmd type 0x%02X\n", cmd->cmd_type);
                return -2;
            }

            if (dump) {
                rt_kprintf("cmd[0x%02x] -> delay %u, data:", cmd->cmd_type, cmd->cmd_delay);
                for (int i = 0; i < cmd->cmd_size; i++)
                    rt_kprintf("%02X ", cmd->cmd_data[i]);
                rt_kprintf("\n");
            }

            if (cmd->cmd_delay)
                rt_hw_us_delay((uint64_t)(cmd->cmd_delay) * 1000);
        }

        pcmd += sizeof(k_connector_cmd_slice) + cmd->cmd_size;
    } while (pcmd < pcmd_end);

    return 0;
}

k_u32 dsi_read_chip_id(const struct panel_desc* desc)
{
    if (!desc)
        return 0xDEADBEEF;

    k_u8 vc = desc->bus.dsi.vc_id;
    k_u8 id[3] = { 0x03, 0x00, 0x00 };

    if (dwc_dsi_send_packet(0x37, vc, id, 1, 1) != 0)
        return 0xDEADBEEF;

    if (dwc_dsi_dcs_read(0x04, &id[0], 3, vc) != 3)
        return 0xDEADBEEF;

    return (k_u32)((id[0] << 16) | (id[1] << 8) | id[2]);
}

const struct panel_bus_ops dsi_bus_ops = {
    .init    = dsi_bus_init,
    .enable  = dsi_bus_enable,
    .disable = NULL,
};
