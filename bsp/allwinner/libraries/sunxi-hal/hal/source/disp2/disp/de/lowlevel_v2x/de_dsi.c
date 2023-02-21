/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#include "de_feat.h"
#include "de_dsi_type.h"
#include "de_dsi.h"

#define do_div(n,base) ({                   \
                u32 __base = (base);                \
                u32 __rem;                      \
                __rem = ((u64)(n)) % __base;            \
                (n) = ((u64)(n)) / __base;              \
                if (__rem > __base / 2) \
                    ++(n); \
                __rem;                          \
            })

#if defined(SUPPORT_DSI)

static volatile struct __de_dsi_dev_t *dsi_dev[DEVICE_DSI_NUM];
static volatile struct __de_dsi_dphy_dev_t *dphy_dev[DEVICE_DSI_NUM];

u32 dsi_pixel_bits[4] = { 24, 24, 18, 16 };
u32 dsi_lane_den[4] = { 0x1, 0x3, 0x7, 0xf };
u32 tcon_div = 4;

s32 dsi_delay_ms(u32 ms)
{
    disp_delay_ms(ms);

    return 0;
}

s32 dsi_delay_us(u32 us)
{
    disp_delay_us(us);

    return 0;
}

s32 dsi_set_reg_base(u32 sel, uintptr_t base)
{
    dsi_dev[sel] = (struct __de_dsi_dev_t *) base;
    dphy_dev[sel] = (struct __de_dsi_dphy_dev_t *) (base + 0x1000);

    return 0;
}

u32 dsi_get_reg_base(u32 sel)
{
    return (u32) (uintptr_t) dsi_dev[sel];
}

u32 dsi_get_start_delay(u32 sel)
{
    return dsi_dev[sel]->dsi_basic_ctl1.bits.video_start_delay;
}

u32 dsi_get_cur_line(u32 sel)
{
    u32 curr_line = dsi_dev[sel]->dsi_debug_video0.bits.video_curr_line;
    u32 vt = dsi_dev[sel]->dsi_basic_size1.bits.vt;
    u32 vsa = dsi_dev[sel]->dsi_basic_size0.bits.vsa;
    u32 vbp = dsi_dev[sel]->dsi_basic_size0.bits.vbp;
    u32 y = dsi_dev[sel]->dsi_basic_size1.bits.vact;
    u32 vfp = vt - vsa - vbp - y;

    curr_line += vfp;
    if (curr_line > vt)
        curr_line -= vt;

    return curr_line;
}

s32 dsi_irq_enable(u32 sel, enum __dsi_irq_id_t id)
{
    dsi_dev[sel]->dsi_gint0.bits.dsi_irq_en |= (1 << id);

    return 0;
}

s32 dsi_irq_disable(u32 sel, enum __dsi_irq_id_t id)
{
    dsi_dev[sel]->dsi_gint0.bits.dsi_irq_en &= ~(1 << id);

    return 0;
}

u32 dsi_irq_query(u32 sel, enum __dsi_irq_id_t id)
{
    u32 en, fl;

    en = dsi_dev[sel]->dsi_gint0.bits.dsi_irq_en;
    fl = dsi_dev[sel]->dsi_gint0.bits.dsi_irq_flag;
    if (en & fl & (1 << id)) {
        dsi_dev[sel]->dsi_gint0.bits.dsi_irq_flag |= (1 << id);
        return 1;
    } else {
        return 0;
    }
}

s32 dsi_inst_busy(u32 sel)
{
    return dsi_dev[sel]->dsi_basic_ctl0.bits.inst_st;
}

s32 dsi_start(u32 sel, enum __dsi_start_t func)
{
    switch (func) {
    case DSI_START_TBA:
        dsi_dev[sel]->dsi_inst_jump_sel.dwval =
            DSI_INST_ID_TBA << (4 * DSI_INST_ID_LP11)
            | DSI_INST_ID_END << (4 * DSI_INST_ID_TBA);
        break;
    case DSI_START_HSTX:
        dsi_dev[sel]->dsi_inst_jump_sel.dwval =
            DSI_INST_ID_HSC << (4 * DSI_INST_ID_LP11)
            | DSI_INST_ID_NOP << (4 * DSI_INST_ID_HSC)
            | DSI_INST_ID_HSD << (4 * DSI_INST_ID_NOP)
            | DSI_INST_ID_DLY << (4 * DSI_INST_ID_HSD)
            | DSI_INST_ID_NOP << (4 * DSI_INST_ID_DLY)
            | DSI_INST_ID_END << (4 * DSI_INST_ID_HSCEXIT);
        break;
    case DSI_START_LPTX:
        dsi_dev[sel]->dsi_inst_jump_sel.dwval =
            DSI_INST_ID_LPDT << (4 * DSI_INST_ID_LP11)
            | DSI_INST_ID_END << (4 * DSI_INST_ID_LPDT);
        break;
    case DSI_START_LPRX:
        dsi_dev[sel]->dsi_inst_jump_sel.dwval =
            DSI_INST_ID_LPDT << (4 * DSI_INST_ID_LP11)
            | DSI_INST_ID_DLY << (4 * DSI_INST_ID_LPDT)
            | DSI_INST_ID_TBA << (4 * DSI_INST_ID_DLY)
            | DSI_INST_ID_END << (4 * DSI_INST_ID_TBA);
        break;
    case DSI_START_HSC:
        dsi_dev[sel]->dsi_inst_jump_sel.dwval =
            DSI_INST_ID_HSC << (4 * DSI_INST_ID_LP11)
            | DSI_INST_ID_END << (4 * DSI_INST_ID_HSC);
        break;
    case DSI_START_HSD:
        dsi_dev[sel]->dsi_inst_jump_sel.dwval =
            DSI_INST_ID_NOP << (4 * DSI_INST_ID_LP11)
            | DSI_INST_ID_HSD << (4 * DSI_INST_ID_NOP)
            | DSI_INST_ID_DLY << (4 * DSI_INST_ID_HSD)
            | DSI_INST_ID_NOP << (4 * DSI_INST_ID_DLY)
            | DSI_INST_ID_END << (4 * DSI_INST_ID_HSCEXIT);
        break;
    default:
        dsi_dev[sel]->dsi_inst_jump_sel.dwval =
            DSI_INST_ID_END << (4 * DSI_INST_ID_LP11);
        break;
    }
    dsi_dev[sel]->dsi_basic_ctl0.bits.inst_st = 0;
    dsi_dev[sel]->dsi_basic_ctl0.bits.inst_st = 1;
    if (func == DSI_START_HSC)
        dsi_dev[sel]->dsi_inst_func[DSI_INST_ID_LP11].bits.lane_cen =
            (dsi_dev[sel]->dsi_pixel_ctl0.bits.pd_plug_dis) ? 0 : 1;

    return 0;
}

s32 dsi_open(u32 sel, struct disp_panel_para *panel)
{
    if (panel->lcd_fresh_mode == 0) {
        dsi_irq_enable(sel, DSI_IRQ_VIDEO_VBLK);
        dsi_start(sel, DSI_START_HSD);
        /*
         *  while (dphy_dev[sel]->dphy_dbg0.bits.lptx_sta_clk != 5);
         *  dphy_dev[sel]->dphy_ana1.bits.reg_vttmode =  1;
         *  dphy_dev[sel]->dphy_ana2.bits.enp2s_cpu =
         *  dsi_lane_den[panel->lcd_dsi_lane-1];
         */
    }

    return 0;
}

s32 dsi_close(u32 sel)
{
    dsi_irq_disable(sel, DSI_IRQ_VIDEO_VBLK);
    dsi_dev[sel]->dsi_inst_jump_cfg[0].bits.jump_cfg_en = 1;
    dsi_delay_ms(30);
    /*
     * while (dphy_dev[sel]->dphy_dbg0.bits.lptx_sta_d0 == 5);
     * dphy_dev[sel]->dphy_ana2.bits.enp2s_cpu  = 0;
     * dphy_dev[sel]->dphy_ana1.bits.reg_vttmode =  1;
     */

    return 0;
}

/**
 * @name       dsi_mode_switch
 * @brief      switch dsi mode between cmd and video mode
 * @param[IN]  sel: dsi module index; en:1-->video mode
 *             0--> cmd mode
 * @return     alway return 0
 */
__s32 dsi_mode_switch(__u32 sel, __u32 cmd_en, __u32 lp_en)
{
    return 0;
}

__s32 dsi_gen_short_rd(__u32 sel, __u8 *para_p, __u8 para_num, __u8 *result)
{
    return 0;
}

/* 0: normal; -1:under flow; */
s32 dsi_get_status(u32 sel)
{
    if (dsi_dev[sel]->dsi_debug_inst.bits.trans_low_flag ||
        dsi_dev[sel]->dsi_debug_inst.bits.trans_fast_flag) {
        dsi_dev[sel]->dsi_debug_inst.bits.trans_low_flag = 1;
        dsi_dev[sel]->dsi_debug_inst.bits.trans_fast_flag = 1;
        return -1;
    }
    return 0;
}


s32 dsi_tri_start(u32 sel)
{
    dsi_start(sel, DSI_START_HSTX);
#if 0
    while (dsi_dev[sel]->dsi_debug_inst.bits.curr_instru_num
        != DSI_INST_ID_HSD)
        ;
    while (dphy_dev[sel]->dphy_dbg0.bits.lptx_sta_d0 != 5)
        ;
#endif

    return 0;
}

s32 dsi_dcs_wr(u32 sel, u8 cmd, u8 *para_p, u32 para_num)
{
    volatile u8 *p = (u8 *) dsi_dev[sel]->dsi_cmd_tx;
    u32 count = 0;

    while ((dsi_dev[sel]->dsi_basic_ctl0.bits.inst_st == 1)
        && (count < 50)) {
        count++;
        dsi_delay_us(100);
    }
    if (count >= 50)
        dsi_dev[sel]->dsi_basic_ctl0.bits.inst_st = 0;

    if (para_num == 0) {

        *(p++) = DSI_DT_DCS_WR_P0;
        *(p++) = cmd;
        *(p++) = 0x00;
    } else if (para_num == 1) {
        *(p++) = DSI_DT_DCS_WR_P1;
        *(p++) = cmd;
        *(p++) = *para_p;
    } else {
        *(p++) = DSI_DT_DCS_LONG_WR;
        *(p++) = (para_num + 1) >> 0 & 0xff;
        *(p++) = (para_num + 1) >> 8 & 0xff;
    }
    *(p++) = dsi_ecc_pro(dsi_dev[sel]->dsi_cmd_tx[0].dwval);

    if (para_num > 1) {
        u16 crc, i;
        *(p++) = cmd;
        for (i = 0; i < para_num; i++)
            *(p++) = *(para_p + i);
        crc =
            dsi_crc_pro((u8 *) (dsi_dev[sel]->dsi_cmd_tx + 1),
                para_num + 1);
        *(p++) = (crc >> 0) & 0xff;
        *(p++) = (crc >> 8) & 0xff;
        dsi_dev[sel]->dsi_cmd_ctl.bits.tx_size =
            4 + 1 + para_num + 2 - 1;
    } else {
        dsi_dev[sel]->dsi_cmd_ctl.bits.tx_size = 4 - 1;
    }
    dsi_start(sel, DSI_START_LPTX);

    return 0;
}

s32 dsi_dcs_wr_index(u32 sel, u8 index)
{
    return 0;
}

s32 dsi_dcs_wr_data(u32 sel, u8 data)
{
    return 0;
}

s32 dsi_dcs_wr_0para(u32 sel, u8 cmd)
{
    u8 tmp;

    return dsi_dcs_wr(0, cmd, &tmp, 0);
}

s32 dsi_dcs_wr_1para(u32 sel, u8 cmd, u8 para)
{
    u8 tmp = para;

    return dsi_dcs_wr(0, cmd, &tmp, 1);
}

s32 dsi_dcs_wr_2para(u32 sel, u8 cmd, u8 para1, u8 para2)
{
    u8 tmp[2];

    tmp[0] = para1;
    tmp[1] = para2;
    return dsi_dcs_wr(0, cmd, tmp, 2);
}

s32 dsi_dcs_wr_3para(u32 sel, u8 cmd, u8 para1, u8 para2, u8 para3)
{
    u8 tmp[3];

    tmp[0] = para1;
    tmp[1] = para2;
    tmp[2] = para3;
    return dsi_dcs_wr(0, cmd, tmp, 3);
}

s32 dsi_dcs_wr_4para(u32 sel, u8 cmd, u8 para1, u8 para2, u8 para3, u8 para4)
{
    u8 tmp[4];

    tmp[0] = para1;
    tmp[1] = para2;
    tmp[2] = para3;
    tmp[3] = para4;
    return dsi_dcs_wr(0, cmd, tmp, 4);
}

s32 dsi_dcs_wr_5para(u32 sel, u8 cmd, u8 para1, u8 para2, u8 para3, u8 para4,
             u8 para5)
{
    u8 tmp[5];

    tmp[0] = para1;
    tmp[1] = para2;
    tmp[2] = para3;
    tmp[3] = para4;
    tmp[4] = para5;
    return dsi_dcs_wr(0, cmd, tmp, 5);
}

s32 dsi_dcs_wr_memory(u32 sel, u32 *p_data, u32 length)
{
    u32 tx_cntr = length;
    u32 tx_num;
    u32 *tx_p = p_data;
    u8 para[256];
    u32 i;
    u32 start = 1;

    while (tx_cntr) {
        if (tx_cntr >= 83)
            tx_num = 83;
        else
            tx_num = tx_cntr;
        tx_cntr -= tx_num;

        for (i = 0; i < tx_num; i++) {
            para[i * 3 + 0] = (*tx_p >> 16) & 0xff;
            para[i * 3 + 1] = (*tx_p >> 8) & 0xff;
            para[i * 3 + 2] = (*tx_p >> 0) & 0xff;
            tx_p++;
        }

        if (start) {
            dsi_dcs_wr(sel, DSI_DCS_WRITE_MEMORY_START, para,
                   tx_num * 3);
            start = 0;
        } else {
            dsi_dcs_wr(sel, DSI_DCS_WRITE_MEMORY_CONTINUE, para,
                   tx_num * 3);
        }
    }
    return 0;
}

s32 dsi_gen_wr(u32 sel, u8 cmd, u8 *para_p, u32 para_num)
{
    volatile u8 *p = (u8 *) dsi_dev[sel]->dsi_cmd_tx;
    while (dsi_inst_busy(sel))
        ;
    if (para_num == 0) {
        *(p++) = DSI_DT_GEN_WR_P1;
        *(p++) = cmd;
        *(p++) = 0x00;
    } else if (para_num == 1) {
        *(p++) = DSI_DT_GEN_WR_P2;
        *(p++) = cmd;
        *(p++) = *para_p;
    } else {
        *(p++) = DSI_DT_GEN_LONG_WR;
        *(p++) = (para_num + 1) >> 0 & 0xff;
        *(p++) = (para_num + 1) >> 8 & 0xff;
    }
    *(p++) = dsi_ecc_pro(dsi_dev[sel]->dsi_cmd_tx[0].dwval);

    if (para_num > 1) {
        __u16 crc, i;
        *(p++) = cmd;
        for (i = 0; i < para_num; i++)
            *(p++) = *(para_p + i);
        crc = dsi_crc_pro((u8 *) (dsi_dev[sel]->dsi_cmd_tx + 1),
            para_num + 1);
        *(p++) = (crc >> 0) & 0xff;
        *(p++) = (crc >> 8) & 0xff;
        dsi_dev[sel]->dsi_cmd_ctl.bits.tx_size =
            4 + 1 + para_num + 2 - 1;
    } else {
        dsi_dev[sel]->dsi_cmd_ctl.bits.tx_size = 4 - 1;
    }
    dsi_start(sel, DSI_START_LPTX);
    return 0;
}

s32 dsi_set_max_ret_size(u32 sel, u32 size)
{
    dsi_dev[sel]->dsi_cmd_tx[0].bits.byte0 = DSI_DT_MAX_RET_SIZE;
    dsi_dev[sel]->dsi_cmd_tx[0].bits.byte1 = (size >> 0) & 0xff;
    dsi_dev[sel]->dsi_cmd_tx[0].bits.byte2 = (size >> 8) & 0xff;
    dsi_dev[sel]->dsi_cmd_tx[0].bits.byte3 =
        dsi_ecc_pro(dsi_dev[sel]->dsi_cmd_tx[0].dwval);
    dsi_dev[sel]->dsi_cmd_ctl.bits.tx_size = 4 - 1;
    dsi_start(sel, DSI_START_LPTX);
    return 0;
}

s32 dsi_dcs_rd(u32 sel, u8 cmd, u8 *para_p, u32 *num_p)
{
    u32 num, i;
    u32 count = 0;

    dsi_dev[sel]->dsi_cmd_tx[0].bits.byte0 = DSI_DT_DCS_RD_P0;
    dsi_dev[sel]->dsi_cmd_tx[0].bits.byte1 = cmd;
    dsi_dev[sel]->dsi_cmd_tx[0].bits.byte2 = 0x00;
    dsi_dev[sel]->dsi_cmd_tx[0].bits.byte3 =
        dsi_ecc_pro(dsi_dev[sel]->dsi_cmd_tx[0].dwval);
    dsi_dev[sel]->dsi_cmd_ctl.bits.tx_size = 4 - 1;

    dsi_start(sel, DSI_START_LPRX);

    while ((dsi_dev[sel]->dsi_basic_ctl0.bits.inst_st == 1)
        && (count < 50)) {
        count++;
        dsi_delay_us(100);
    }
    if (count >= 50)
        dsi_dev[sel]->dsi_basic_ctl0.bits.inst_st = 0;

    if (dsi_dev[sel]->dsi_cmd_ctl.bits.rx_flag) {
        if (dsi_dev[sel]->dsi_cmd_ctl.bits.rx_overflow)
            return -1;
        if (dsi_dev[sel]->dsi_cmd_rx[0].bits.byte0 == DSI_DT_ACK_ERR)
            return -1;

        if (dsi_dev[sel]->dsi_cmd_rx[0].bits.byte0
            == DSI_DT_DCS_RD_R1) {
            num = 1;
            *(para_p + 0) = dsi_dev[sel]->dsi_cmd_rx[0].bits.byte1;
        } else if (dsi_dev[sel]->dsi_cmd_rx[0].bits.byte0 ==
               (u8) DSI_DT_DCS_RD_R2) {
            num = 2;
            *(para_p + 0) = dsi_dev[sel]->dsi_cmd_rx[0].bits.byte1;
            *(para_p + 1) = dsi_dev[sel]->dsi_cmd_rx[0].bits.byte2;
        } else if (dsi_dev[sel]->dsi_cmd_rx[0].bits.byte0 ==
               (u8) DSI_DT_DCS_LONG_RD_R) {
            num = dsi_dev[sel]->dsi_cmd_ctl.bits.rx_size + 1 - 6;
            for (i = 0; i < num; i++) {
                *(para_p + i) =
                    *((u8 *) dsi_dev[sel]->dsi_cmd_rx + 4 + i);
            }
        } else {
            num = 0;
            return -1;
        }
        *num_p = num;
    }

    return 0;
}

s32 dsi_dcs_rd_memory(u32 sel, u32 *p_data, u32 length)
{
    u32 rx_cntr = length;
    u32 rx_curr;
    u32 *rx_p = p_data;
    u32 i;
    u32 start = 1;

    u8 rx_bf[32];
    u32 rx_num;

    dsi_set_max_ret_size(sel, 24);

    while (rx_cntr) {
        if (rx_cntr >= 8) {
            rx_curr = 8;
        } else {
            rx_curr = rx_cntr;
            dsi_set_max_ret_size(sel, rx_curr * 3);
        }
        rx_cntr -= rx_curr;

        if (start) {
            dsi_dcs_rd(sel, DSI_DCS_READ_MEMORY_START, rx_bf,
                   &rx_num);
            start = 0;
        } else {
            dsi_dcs_rd(sel, DSI_DCS_READ_MEMORY_CONTINUE, rx_bf,
                   &rx_num);
        }

        if (rx_num != rx_curr * 3)
            return -1;

        for (i = 0; i < rx_curr; i++) {
            *rx_p &= 0xff000000;
            *rx_p |= 0xff000000;
            *rx_p |= (u32) *(rx_bf + 4 + i * 3 + 0) << 16;
            *rx_p |= (u32) *(rx_bf + 4 + i * 3 + 1) << 8;
            *rx_p |= (u32) *(rx_bf + 4 + i * 3 + 2) << 0;
            rx_p++;
        }
    }
    return 0;
}

static s32 dsi_dphy_cfg(u32 sel, struct disp_panel_para *panel)
{
    struct __disp_dsi_dphy_timing_t *dphy_timing_p;
    struct __disp_dsi_dphy_timing_t dphy_timing_cfg1 = {
        /* lp_clk_div(100ns) hs_prepare(70ns) hs_trail(100ns) */
        14,
        6,
        10,
        /* clk_prepare(70ns) clk_zero(300ns) clk_pre */
        7,
        50,
        3,
        /*
         * clk_post: 400*6.734 for nop inst  2.5us
         * clk_trail: 200ns
         * hs_dly_mode
         */
        10,
        30,
        0,
        /* hs_dly lptx_ulps_exit hstx_ana1 hstx_ana0 */
        10,
        3,
        3,
        3,
    };

    dphy_dev[sel]->dphy_gctl.bits.module_en = 0;
    dphy_dev[sel]->dphy_gctl.bits.lane_num = panel->lcd_dsi_lane - 1;

    dphy_dev[sel]->dphy_tx_ctl.bits.hstx_clk_cont = 1;

    dphy_timing_p = &dphy_timing_cfg1;

    dphy_dev[sel]->dphy_tx_time0.bits.lpx_tm_set =
        dphy_timing_p->lp_clk_div;
    dphy_dev[sel]->dphy_tx_time0.bits.hs_pre_set =
        dphy_timing_p->hs_prepare;
    dphy_dev[sel]->dphy_tx_time0.bits.hs_trail_set =
        dphy_timing_p->hs_trail;
    dphy_dev[sel]->dphy_tx_time1.bits.ck_prep_set =
        dphy_timing_p->clk_prepare;
    dphy_dev[sel]->dphy_tx_time1.bits.ck_zero_set = dphy_timing_p->clk_zero;
    dphy_dev[sel]->dphy_tx_time1.bits.ck_pre_set = dphy_timing_p->clk_pre;
    dphy_dev[sel]->dphy_tx_time1.bits.ck_post_set = dphy_timing_p->clk_post;
    dphy_dev[sel]->dphy_tx_time2.bits.ck_trail_set =
        dphy_timing_p->clk_trail;
    dphy_dev[sel]->dphy_tx_time2.bits.hs_dly_mode = 0;
    dphy_dev[sel]->dphy_tx_time2.bits.hs_dly_set = 0;
    dphy_dev[sel]->dphy_tx_time3.bits.lptx_ulps_exit_set = 0;
    dphy_dev[sel]->dphy_tx_time4.bits.hstx_ana0_set = 3;
    dphy_dev[sel]->dphy_tx_time4.bits.hstx_ana1_set = 3;
#ifndef SUPPORT_COMBO_DPHY
    dphy_dev[sel]->dphy_gctl.bits.module_en = 1;
#endif
#if 0
    dphy_dev[sel]->dphy_ana1.bits.reg_vttmode = 0;
    dphy_dev[sel]->dphy_ana0.bits.reg_selsck = 0;
    dphy_dev[sel]->dphy_ana0.bits.reg_pws = 1;
    dphy_dev[sel]->dphy_ana0.bits.reg_sfb = 0;
    dphy_dev[sel]->dphy_ana0.bits.reg_dmpc = 1;
    dphy_dev[sel]->dphy_ana0.bits.reg_dmpd =
        dsi_lane_den[panel->lcd_dsi_lane-1];
    dphy_dev[sel]->dphy_ana0.bits.reg_slv = 0x7;
    dphy_dev[sel]->dphy_ana0.bits.reg_den =
        dsi_lane_den[panel->lcd_dsi_lane-1];
    dphy_dev[sel]->dphy_ana1.bits.reg_svtt = 7;
    dphy_dev[sel]->dphy_ana4.bits.reg_ckdv = 0x1;
    dphy_dev[sel]->dphy_ana4.bits.reg_tmsc = 0x1;
    dphy_dev[sel]->dphy_ana4.bits.reg_tmsd = 0x1;
    dphy_dev[sel]->dphy_ana4.bits.reg_txdnsc = 0x1;
    dphy_dev[sel]->dphy_ana4.bits.reg_txdnsd = 0x1;
    dphy_dev[sel]->dphy_ana4.bits.reg_txpusc = 0x1;
    dphy_dev[sel]->dphy_ana4.bits.reg_txpusd = 0x1;
    dphy_dev[sel]->dphy_ana4.bits.reg_dmplvc = 0x1;
    dphy_dev[sel]->dphy_ana4.bits.reg_dmplvd =
        dsi_lane_den[panel->lcd_dsi_lane-1];

    dphy_dev[sel]->dphy_ana2.bits.enib = 1;
    dsi_delay_us(5);
    dphy_dev[sel]->dphy_ana3.bits.enldor = 1;
    dphy_dev[sel]->dphy_ana3.bits.enldoc = 1;
    dphy_dev[sel]->dphy_ana3.bits.enldod = 1;
    dsi_delay_us(1);
    dphy_dev[sel]->dphy_ana3.bits.envttc = 1;
    dphy_dev[sel]->dphy_ana3.bits.envttd =
        dsi_lane_den[panel->lcd_dsi_lane-1];
    dsi_delay_us(1);
    dphy_dev[sel]->dphy_ana3.bits.endiv = 1;
    dsi_delay_us(1);
    dphy_dev[sel]->dphy_ana2.bits.enck_cpu = 1;
    dsi_delay_us(1);

    dphy_dev[sel]->dphy_ana1.bits.reg_vttmode = 1;
    dphy_dev[sel]->dphy_ana2.bits.enp2s_cpu =
        dsi_lane_den[panel->lcd_dsi_lane-1];

    dphy_dev[sel]->dphy_dbg1.bits.lptx_set_ck = 0x3;
    dphy_dev[sel]->dphy_dbg1.bits.lptx_set_d0 = 0x3;
    dphy_dev[sel]->dphy_dbg1.bits.lptx_set_d1 = 0x3;
    dphy_dev[sel]->dphy_dbg1.bits.lptx_set_d2 = 0x3;
    dphy_dev[sel]->dphy_dbg1.bits.lptx_set_d3 = 0x3;
    dphy_dev[sel]->dphy_dbg1.bits.lptx_dbg_en = 1;
#endif
    return 0;
}
#ifdef SUPPORT_COMBO_DPHY
/*description: dsi comb phy pll configuration
 * @param sel:dsi channel select
 * @param dclk: pixel clk
 * @param mode: dsi operation mode,0:video mode; 1:command mode;
 * @param format:dis pixel format
 * @param lane: dis output lane number
 * return ret: clk
 */
u32 dsi_comb_dphy_pll_set(__u32 sel, __u32 dclk, __u32 mode, __u32 format,
              __u32 lane)
{
    u64 frq;
    u32 n;
    u32 div_p, div_m0;
    u8 pixel_bits[3][4] = {
        { 24, 24, 18, 16 }, { 24, 24, 16, 0 }, { 24, 24, 18, 16 } };

    frq = dclk * pixel_bits[mode][format] / lane * 1000000; /* unit:Hz */
    if (frq <= 264000000) {
        frq = frq * 16;
        do_div(frq, 24000000);
        n = frq;
        div_p = 7;
        div_m0 = 1;
    } else if (frq <= 536000000) {
        frq = frq * 8;
        do_div(frq, 24000000);
        n = frq;
        div_p = 7;
        div_m0 = 0;
    } else if (frq <= 1072000000) {
        frq = frq * 4;
        do_div(frq, 24000000);
        n = frq;
        div_p = 3;
        div_m0 = 0;
    } else if (frq <= 2144000000) {
        frq = frq * 2;
        do_div(frq, 24000000);
        n = frq;
        div_p = 1;
        div_m0 = 0;
    } else {
        do_div(frq, 24000000);
        n = frq;
        div_p = 0;
        div_m0 = 0;
    }
    dphy_dev[sel]->dphy_pll_reg0.bits.n =
        n; /* HS_clk:24MHz*n/(p+1)/(m0+1); */
           /* LP_clk_src:24MHz*n/(p+1)/(m0+1)/(m1+1) */
    dphy_dev[sel]->dphy_pll_reg0.bits.p = div_p;
    dphy_dev[sel]->dphy_pll_reg0.bits.m0 = div_m0;
    dphy_dev[sel]->dphy_pll_reg0.bits.m1 = 2; /*?? */
    dphy_dev[sel]->dphy_pll_reg2.dwval = 0; /*Disable sdm*/

    return 24000000 * n / (div_p + 1) / (div_m0 + 1);
}

__s32 dsi_dphy_open(__u32 sel, struct disp_panel_para *panel)
{
    u32 i = 0;
    u32 lane_den = 0;
    for (i = 0; i < panel->lcd_dsi_lane; i++)
        lane_den |= (1 << i);

    dphy_dev[sel]->dphy_ana4.bits.reg_ib = 2;
    dphy_dev[sel]->dphy_ana4.bits.reg_dmplvc = 0;
    dphy_dev[sel]->dphy_ana4.bits.reg_dmplvd = 4;
    dphy_dev[sel]->dphy_ana4.bits.reg_vtt_set = 3;
    dphy_dev[sel]->dphy_ana4.bits.reg_ckdv = 3;
    dphy_dev[sel]->dphy_ana4.bits.reg_tmsd = 1;
    dphy_dev[sel]->dphy_ana4.bits.reg_tmsc = 1;
    dphy_dev[sel]->dphy_ana4.bits.reg_txpusd = 2;
    dphy_dev[sel]->dphy_ana4.bits.reg_txpusc = 3;
    dphy_dev[sel]->dphy_ana4.bits.reg_txdnsd = 2;

    dphy_dev[sel]->dphy_ana2.bits.enck_cpu = 1;

    dphy_dev[sel]->dphy_ana2.bits.enib = 1;
    dphy_dev[sel]->dphy_ana3.bits.enldor = 1;
    dphy_dev[sel]->dphy_ana3.bits.enldoc = 1;
    dphy_dev[sel]->dphy_ana3.bits.enldod = 1;
    dphy_dev[sel]->dphy_ana0.bits.reg_plr = 4;
    dphy_dev[sel]->dphy_ana0.bits.reg_sfb = 1;
    dphy_dev[sel]->dphy_ana0.bits.reg_selsck = 0;
    dphy_dev[sel]->dphy_ana0.bits.reg_rsd = 0;
    dphy_dev[sel]->combo_phy_reg0.bits.en_cp = 1;
    dsi_comb_dphy_pll_set(sel, panel->lcd_dclk_freq, panel->lcd_dsi_if,
                  panel->lcd_dsi_format, panel->lcd_dsi_lane);


    dphy_dev[sel]->dphy_ana4.bits.en_mipi = 1;
    dphy_dev[sel]->dphy_ana4.bits.reg_txdnsc = 3;
    dphy_dev[sel]->combo_phy_reg0.bits.en_mipi = 1;
    dphy_dev[sel]->combo_phy_reg0.bits.en_comboldo = 1;
    dphy_dev[sel]->combo_phy_reg2.bits.hs_stop_dly = 20;
    dsi_delay_us(1);

    dphy_dev[sel]->dphy_ana3.bits.envttc = 1;
    dphy_dev[sel]->dphy_ana3.bits.envttd = lane_den;
    dphy_dev[sel]->dphy_ana3.bits.endiv = 1;
    dphy_dev[sel]->dphy_ana2.bits.enck_cpu = 1;
    dphy_dev[sel]->dphy_ana1.bits.reg_vttmode = 1;
#ifdef CONFIG_ARCH_SUN50IW10
    i = readl(ioremap(0x03000024, 4));
    if ((i & 0x00000007) > 0)
        dphy_dev[sel]->dphy_ana1.dwval |= 0x00000020;
    else
        dphy_dev[sel]->dphy_ana1.dwval &= 0xffffffDf;
#endif
    dphy_dev[sel]->dphy_ana2.bits.enp2s_cpu = lane_den;

    dphy_dev[sel]->dphy_gctl.bits.module_en = 1;
    return 0;
}

__s32 dsi_dphy_close(__u32 sel)
{
    dphy_dev[sel]->dphy_ana2.bits.enck_cpu = 0;
    dphy_dev[sel]->dphy_ana3.bits.endiv = 0;

    dphy_dev[sel]->dphy_ana2.bits.enib = 0;
    dphy_dev[sel]->dphy_ana3.bits.enldor = 0;
    dphy_dev[sel]->dphy_ana3.bits.enldoc = 0;
    dphy_dev[sel]->dphy_ana3.bits.enldod = 0;
    dphy_dev[sel]->dphy_ana3.bits.envttc = 0;
    dphy_dev[sel]->dphy_ana3.bits.envttd = 0;
    return 0;
}
__s32 lvds_combphy_close(__u32 sel)
{
    dphy_dev[sel]->combo_phy_reg1.dwval = 0x0;
    dphy_dev[sel]->combo_phy_reg0.dwval = 0x0;
    dphy_dev[sel]->dphy_ana4.dwval = 0x0;
    dphy_dev[sel]->dphy_ana3.dwval = 0x0;
    dphy_dev[sel]->dphy_ana1.dwval = 0x0;

    return 0;
}

__s32 lvds_combphy_open(__u32 sel, struct disp_panel_para *panel)
{
    dphy_dev[sel]->combo_phy_reg1.dwval = 0x43;
    dphy_dev[sel]->combo_phy_reg0.dwval = 0x1;
    dsi_delay_us(5);
    dphy_dev[sel]->combo_phy_reg0.dwval = 0x5;
    dsi_delay_us(5);
    dphy_dev[sel]->combo_phy_reg0.dwval = 0x7;
    dsi_delay_us(5);
    dphy_dev[sel]->combo_phy_reg0.dwval = 0xf;

    dphy_dev[sel]->dphy_ana4.dwval = 0x84000000;
    dphy_dev[sel]->dphy_ana3.dwval = 0x01040000;
    dphy_dev[sel]->dphy_ana2.dwval =
        dphy_dev[sel]->dphy_ana2.dwval & (0x0 << 1);
    dphy_dev[sel]->dphy_ana1.dwval = 0x0;

    return 0;
}
#endif

u32 dsi_io_open(u32 sel, struct disp_panel_para *panel)
{
#ifdef SUPPORT_COMBO_DPHY
    dsi_dphy_open(sel, panel);
#else
    dphy_dev[sel]->dphy_ana1.bits.reg_vttmode = 0;
    dphy_dev[sel]->dphy_ana0.bits.reg_selsck = 0;
    dphy_dev[sel]->dphy_ana0.bits.reg_pws = 1;
    dphy_dev[sel]->dphy_ana0.bits.reg_sfb = 0;
    dphy_dev[sel]->dphy_ana1.bits.reg_csmps = 1;
    dphy_dev[sel]->dphy_ana0.bits.reg_dmpc = 1;
    dphy_dev[sel]->dphy_ana0.bits.reg_dmpd =
        dsi_lane_den[panel->lcd_dsi_lane - 1];
    dphy_dev[sel]->dphy_ana0.bits.reg_slv = 0x7;
    dphy_dev[sel]->dphy_ana0.bits.reg_den =
        dsi_lane_den[panel->lcd_dsi_lane - 1];
    dphy_dev[sel]->dphy_ana1.bits.reg_svtt = 7;
    dphy_dev[sel]->dphy_ana4.bits.reg_ckdv = 0x1;
    dphy_dev[sel]->dphy_ana4.bits.reg_tmsc = 0x1;
    dphy_dev[sel]->dphy_ana4.bits.reg_tmsd = 0x1;
    dphy_dev[sel]->dphy_ana4.bits.reg_txdnsc = 0x1;
    dphy_dev[sel]->dphy_ana4.bits.reg_txdnsd = 0x1;
    dphy_dev[sel]->dphy_ana4.bits.reg_txpusc = 0x1;
    dphy_dev[sel]->dphy_ana4.bits.reg_txpusd = 0x1;
    dphy_dev[sel]->dphy_ana4.bits.reg_dmplvc = 0x1;
    dphy_dev[sel]->dphy_ana4.bits.reg_dmplvd =
        dsi_lane_den[panel->lcd_dsi_lane - 1];

    dphy_dev[sel]->dphy_ana2.bits.enib = 1;
    dsi_delay_us(5);
    dphy_dev[sel]->dphy_ana3.bits.enldor = 1;
    dphy_dev[sel]->dphy_ana3.bits.enldoc = 1;
    dphy_dev[sel]->dphy_ana3.bits.enldod = 1;
    dsi_delay_us(1);
    dphy_dev[sel]->dphy_ana3.bits.envttc = 1;
    dphy_dev[sel]->dphy_ana3.bits.envttd =
        dsi_lane_den[panel->lcd_dsi_lane - 1];
    dsi_delay_us(1);
    dphy_dev[sel]->dphy_ana3.bits.endiv = 1;
    dsi_delay_us(1);
    dphy_dev[sel]->dphy_ana2.bits.enck_cpu = 1;
    dsi_delay_us(1);

    dphy_dev[sel]->dphy_ana1.bits.reg_vttmode = 1;
    dphy_dev[sel]->dphy_ana2.bits.enp2s_cpu =
        dsi_lane_den[panel->lcd_dsi_lane - 1];

#endif

    return 0;
}

u32 dsi_io_close(u32 sel)
{
    dphy_dev[sel]->dphy_ana2.bits.enp2s_cpu = 0;
    dphy_dev[sel]->dphy_ana1.bits.reg_vttmode = 0;
    dsi_delay_us(1);
    dphy_dev[sel]->dphy_ana2.bits.enck_cpu = 0;
    dsi_delay_us(1);
    dphy_dev[sel]->dphy_ana3.bits.endiv = 0;
    dsi_delay_us(1);
    dphy_dev[sel]->dphy_ana3.bits.envttd = 0;
    dphy_dev[sel]->dphy_ana3.bits.envttc = 0;
    dsi_delay_us(1);
    dphy_dev[sel]->dphy_ana3.bits.enldod = 0;
    dphy_dev[sel]->dphy_ana3.bits.enldoc = 0;
    dphy_dev[sel]->dphy_ana3.bits.enldor = 0;
    dsi_delay_us(5);
    dphy_dev[sel]->dphy_ana2.bits.enib = 0;

    dphy_dev[sel]->dphy_ana4.bits.reg_dmplvd = 0;
    dphy_dev[sel]->dphy_ana4.bits.reg_dmplvc = 0;
    dphy_dev[sel]->dphy_ana4.bits.reg_txpusd = 0;
    dphy_dev[sel]->dphy_ana4.bits.reg_txpusc = 0;
    dphy_dev[sel]->dphy_ana4.bits.reg_txdnsd = 0;
    dphy_dev[sel]->dphy_ana4.bits.reg_txdnsc = 0;
    dphy_dev[sel]->dphy_ana4.bits.reg_tmsd = 0;
    dphy_dev[sel]->dphy_ana4.bits.reg_tmsc = 0;
    dphy_dev[sel]->dphy_ana4.bits.reg_ckdv = 0;
    dphy_dev[sel]->dphy_ana1.bits.reg_svtt = 0;
    dphy_dev[sel]->dphy_ana0.bits.reg_den = 0;
    dphy_dev[sel]->dphy_ana0.bits.reg_slv = 0;
    dphy_dev[sel]->dphy_ana0.bits.reg_dmpd = 0;
    dphy_dev[sel]->dphy_ana0.bits.reg_dmpc = 0;
    dphy_dev[sel]->dphy_ana1.bits.reg_csmps = 0;
    dphy_dev[sel]->dphy_ana0.bits.reg_sfb = 0;
    dphy_dev[sel]->dphy_ana0.bits.reg_pws = 0;
    dphy_dev[sel]->dphy_ana0.bits.reg_selsck = 0;
    dphy_dev[sel]->dphy_ana1.bits.reg_vttmode = 0;
#ifdef SUPPORT_COMBO_DPHY
    dsi_dphy_close(sel);
#endif

    return 0;
}

s32 dsi_clk_enable(u32 sel, u32 en)
{
    if (en)
        dsi_start(sel, DSI_START_HSC);

    return 0;
}

static s32 dsi_basic_cfg(u32 sel, struct disp_panel_para *panel)
{
    if (panel->lcd_dsi_if == LCD_DSI_IF_COMMAND_MODE) {
        dsi_dev[sel]->dsi_basic_ctl0.bits.ecc_en = 1;
        dsi_dev[sel]->dsi_basic_ctl0.bits.crc_en = 1;
        dsi_dev[sel]->dsi_basic_ctl0.bits.hs_eotp_en = 0;
        dsi_dev[sel]->dsi_basic_ctl1.bits.dsi_mode = 0;
        dsi_dev[sel]->dsi_trans_start.bits.trans_start_set = 10;
        dsi_dev[sel]->dsi_trans_zero.bits.hs_zero_reduce_set = 0;
    } else {
        s32 start_delay = panel->lcd_vt - panel->lcd_y - 10;
        u32 vfp = panel->lcd_vt - panel->lcd_y - panel->lcd_vbp;
        u32 dsi_start_delay;

        /*
         * put start_delay to tcon.
         * set ready sync early to dramfreq, so set start_delay 1
         */
        start_delay = 1;

        dsi_start_delay = panel->lcd_vt - vfp + start_delay;
        if (dsi_start_delay > panel->lcd_vt)
            dsi_start_delay -= panel->lcd_vt;
        if (dsi_start_delay == 0)
            dsi_start_delay = 1;

        dsi_dev[sel]->dsi_basic_ctl0.bits.ecc_en = 1;
        dsi_dev[sel]->dsi_basic_ctl0.bits.crc_en = 1;
        dsi_dev[sel]->dsi_basic_ctl0.bits.hs_eotp_en = 0;
        dsi_dev[sel]->dsi_basic_ctl1.bits.video_start_delay =
            dsi_start_delay;
        dsi_dev[sel]->dsi_basic_ctl1.bits.video_precision_mode_align =
            1;
        dsi_dev[sel]->dsi_basic_ctl1.bits.video_frame_start = 1;
        dsi_dev[sel]->dsi_trans_start.bits.trans_start_set = 10;
        dsi_dev[sel]->dsi_trans_zero.bits.hs_zero_reduce_set = 0;
        dsi_dev[sel]->dsi_basic_ctl1.bits.dsi_mode = 1;

        if (panel->lcd_dsi_if == LCD_DSI_IF_BURST_MODE) {
            u32 line_num, edge0, edge1, sync_point = 40;

            line_num = panel->lcd_ht
                * dsi_pixel_bits[panel->lcd_dsi_format]
                / (8 * panel->lcd_dsi_lane);
            edge1 = sync_point
                + (panel->lcd_x + panel->lcd_hbp + 20)
                * dsi_pixel_bits[panel->lcd_dsi_format]
                / (8 * panel->lcd_dsi_lane);
            edge1 = (edge1 > line_num) ? line_num : edge1;
            edge0 = edge1 + (panel->lcd_x + 40) * tcon_div / 8;
            edge0 = (edge0 > line_num) ? (edge0 - line_num) : 1;
            dsi_dev[sel]->dsi_burst_drq.bits.drq_edge0 = edge0;
            dsi_dev[sel]->dsi_burst_drq.bits.drq_edge1 = edge1;
            dsi_dev[sel]->dsi_tcon_drq.bits.drq_mode = 1;
            dsi_dev[sel]->dsi_burst_line.bits.line_num = line_num;
            dsi_dev[sel]->dsi_burst_line.bits.line_syncpoint =
                sync_point;

            dsi_dev[sel]->dsi_basic_ctl.bits.video_mode_burst = 1;

            if (panel->lcd_dsi_lane == 4) {
                dsi_dev[sel]->dsi_basic_ctl.bits.trail_inv =
                    0xc;
                dsi_dev[sel]->dsi_basic_ctl.bits.trail_fill = 1;
            }
        } else {
            if ((panel->lcd_ht - panel->lcd_x - panel->lcd_hbp)
                < 21) {
                dsi_dev[sel]->dsi_tcon_drq.bits.drq_mode = 0;
            } else {
                dsi_dev[sel]->dsi_tcon_drq.bits.drq_set =
                    (panel->lcd_ht - panel->lcd_x -
                     panel->lcd_hbp - 20)
                    * dsi_pixel_bits[panel->lcd_dsi_format] /
                    (8 * 4);
                dsi_dev[sel]->dsi_tcon_drq.bits.drq_mode = 1;
            }
        }
    }
    dsi_dev[sel]->dsi_inst_func[DSI_INST_ID_LP11].bits.instru_mode =
        DSI_INST_MODE_STOP;
    dsi_dev[sel]->dsi_inst_func[DSI_INST_ID_LP11].bits.lane_cen = 1;
    dsi_dev[sel]->dsi_inst_func[DSI_INST_ID_LP11].bits.lane_den =
        dsi_lane_den[panel->lcd_dsi_lane - 1];
    dsi_dev[sel]->dsi_inst_func[DSI_INST_ID_TBA].bits.instru_mode =
        DSI_INST_MODE_TBA;
    dsi_dev[sel]->dsi_inst_func[DSI_INST_ID_TBA].bits.lane_cen = 0;
    dsi_dev[sel]->dsi_inst_func[DSI_INST_ID_TBA].bits.lane_den = 0x1;
    dsi_dev[sel]->dsi_inst_func[DSI_INST_ID_HSC].bits.instru_mode =
        DSI_INST_MODE_HS;
    dsi_dev[sel]->dsi_inst_func[DSI_INST_ID_HSC].bits.trans_packet =
        DSI_INST_PACK_PIXEL;
    dsi_dev[sel]->dsi_inst_func[DSI_INST_ID_HSC].bits.lane_cen = 1;
    dsi_dev[sel]->dsi_inst_func[DSI_INST_ID_HSC].bits.lane_den = 0;
    dsi_dev[sel]->dsi_inst_func[DSI_INST_ID_HSD].bits.instru_mode =
        DSI_INST_MODE_HS;
    dsi_dev[sel]->dsi_inst_func[DSI_INST_ID_HSD].bits.trans_packet =
        DSI_INST_PACK_PIXEL;
    dsi_dev[sel]->dsi_inst_func[DSI_INST_ID_HSD].bits.lane_cen = 0;
    dsi_dev[sel]->dsi_inst_func[DSI_INST_ID_HSD].bits.lane_den =
        dsi_lane_den[panel->lcd_dsi_lane - 1];
    dsi_dev[sel]->dsi_inst_func[DSI_INST_ID_LPDT].bits.instru_mode =
        DSI_INST_MODE_ESCAPE;
    dsi_dev[sel]->dsi_inst_func[DSI_INST_ID_LPDT].bits.escape_enrty =
        DSI_INST_ESCA_LPDT;
    dsi_dev[sel]->dsi_inst_func[DSI_INST_ID_LPDT].bits.trans_packet =
        DSI_INST_PACK_COMMAND;
    dsi_dev[sel]->dsi_inst_func[DSI_INST_ID_LPDT].bits.lane_cen = 0;
    dsi_dev[sel]->dsi_inst_func[DSI_INST_ID_LPDT].bits.lane_den = 0x1;
    dsi_dev[sel]->dsi_inst_func[DSI_INST_ID_HSCEXIT].bits.instru_mode =
        DSI_INST_MODE_HSCEXIT;
    dsi_dev[sel]->dsi_inst_func[DSI_INST_ID_HSCEXIT].bits.lane_cen = 1;
    dsi_dev[sel]->dsi_inst_func[DSI_INST_ID_HSCEXIT].bits.lane_den = 0;
    dsi_dev[sel]->dsi_inst_func[DSI_INST_ID_NOP].bits.instru_mode =
        DSI_INST_MODE_STOP;
    dsi_dev[sel]->dsi_inst_func[DSI_INST_ID_NOP].bits.lane_cen = 0;
    dsi_dev[sel]->dsi_inst_func[DSI_INST_ID_NOP].bits.lane_den =
        dsi_lane_den[panel->lcd_dsi_lane - 1];
    dsi_dev[sel]->dsi_inst_func[DSI_INST_ID_DLY].bits.instru_mode =
        DSI_INST_MODE_NOP;
    dsi_dev[sel]->dsi_inst_func[DSI_INST_ID_DLY].bits.lane_cen = 1;
    dsi_dev[sel]->dsi_inst_func[DSI_INST_ID_DLY].bits.lane_den =
        dsi_lane_den[panel->lcd_dsi_lane - 1];
    dsi_dev[sel]->dsi_inst_loop_sel.dwval = 2 << (4 * DSI_INST_ID_LP11)
        | 3 << (4 * DSI_INST_ID_DLY);
    dsi_dev[sel]->dsi_inst_loop_num.bits.loop_n0 = 50 - 1;
    dsi_dev[sel]->dsi_inst_loop_num2.bits.loop_n0 = 50 - 1;
    if (panel->lcd_dsi_if == LCD_DSI_IF_COMMAND_MODE) {
        dsi_dev[sel]->dsi_inst_loop_num.bits.loop_n1 = 1 - 1;
        dsi_dev[sel]->dsi_inst_loop_num2.bits.loop_n1 = 1 - 1;
    } else if (panel->lcd_dsi_if == LCD_DSI_IF_VIDEO_MODE) {
        dsi_dev[sel]->dsi_inst_loop_num.bits.loop_n1 = 50 - 1;
        dsi_dev[sel]->dsi_inst_loop_num2.bits.loop_n1 = 50 - 1;
    } else if (panel->lcd_dsi_if == LCD_DSI_IF_BURST_MODE) {
        dsi_dev[sel]->dsi_inst_loop_num.bits.loop_n1 =
            (panel->lcd_ht - panel->lcd_x) * (150)
            / (panel->lcd_dclk_freq * 8) - 50;
        dsi_dev[sel]->dsi_inst_loop_num2.bits.loop_n1 =
            (panel->lcd_ht - panel->lcd_x) * (150)
            / (panel->lcd_dclk_freq * 8) - 50;
    }

    if (panel->lcd_dsi_if == LCD_DSI_IF_COMMAND_MODE) {
        dsi_dev[sel]->dsi_inst_jump_cfg[0].bits.jump_cfg_en = 1;
        dsi_dev[sel]->dsi_inst_jump_cfg[0].bits.jump_cfg_num =
            panel->lcd_y;
    } else {
        dsi_dev[sel]->dsi_inst_jump_cfg[0].bits.jump_cfg_en = 0;
        dsi_dev[sel]->dsi_inst_jump_cfg[0].bits.jump_cfg_num = 1;
    }

    dsi_dev[sel]->dsi_inst_jump_cfg[0].bits.jump_cfg_point =
        DSI_INST_ID_NOP;
    dsi_dev[sel]->dsi_inst_jump_cfg[0].bits.jump_cfg_to =
        DSI_INST_ID_HSCEXIT;
    dsi_dev[sel]->dsi_debug_data.bits.test_data = 0xff;
    dsi_dev[sel]->dsi_gctl.bits.dsi_en = 1;
    return 0;
}

static s32 dsi_packet_cfg(u32 sel, struct disp_panel_para *panel)
{
    if (panel->lcd_dsi_if == LCD_DSI_IF_COMMAND_MODE) {
        dsi_dev[sel]->dsi_pixel_ctl0.bits.pd_plug_dis = 0;
        dsi_dev[sel]->dsi_pixel_ph.bits.vc = panel->lcd_dsi_vc;
        dsi_dev[sel]->dsi_pixel_ph.bits.dt = DSI_DT_DCS_LONG_WR;
        dsi_dev[sel]->dsi_pixel_ph.bits.wc = 1 +
            panel->lcd_x * dsi_pixel_bits[panel->lcd_dsi_format] / 8;
        dsi_dev[sel]->dsi_pixel_ph.bits.ecc =
            dsi_ecc_pro(dsi_dev[sel]->dsi_pixel_ph.dwval);
        dsi_dev[sel]->dsi_pixel_pd.bits.pd_tran0 =
            DSI_DCS_WRITE_MEMORY_START;
        dsi_dev[sel]->dsi_pixel_pd.bits.pd_trann =
            DSI_DCS_WRITE_MEMORY_CONTINUE;
        dsi_dev[sel]->dsi_pixel_pf0.bits.crc_force = 0xffff;
        dsi_dev[sel]->dsi_pixel_pf1.bits.crc_init_line0 = 0xe4e9;
        dsi_dev[sel]->dsi_pixel_pf1.bits.crc_init_linen = 0xf468;
        dsi_dev[sel]->dsi_pixel_ctl0.bits.pixel_format =
            panel->lcd_dsi_format;
    } else {
        dsi_dev[sel]->dsi_pixel_ctl0.bits.pd_plug_dis = 1;
        dsi_dev[sel]->dsi_pixel_ph.bits.vc = panel->lcd_dsi_vc;
        dsi_dev[sel]->dsi_pixel_ph.bits.dt =
            DSI_DT_PIXEL_RGB888 - 0x10 * panel->lcd_dsi_format;
        dsi_dev[sel]->dsi_pixel_ph.bits.wc =
            panel->lcd_x * dsi_pixel_bits[panel->lcd_dsi_format] / 8;
        dsi_dev[sel]->dsi_pixel_ph.bits.ecc =
            dsi_ecc_pro(dsi_dev[sel]->dsi_pixel_ph.dwval);
        dsi_dev[sel]->dsi_pixel_pf0.bits.crc_force = 0xffff;
        dsi_dev[sel]->dsi_pixel_pf1.bits.crc_init_line0 = 0xffff;
        dsi_dev[sel]->dsi_pixel_pf1.bits.crc_init_linen = 0xffff;
        dsi_dev[sel]->dsi_pixel_ctl0.bits.pixel_format =
            8 + panel->lcd_dsi_format;
    }

    if ((panel->lcd_dsi_if == LCD_DSI_IF_VIDEO_MODE)
        || (panel->lcd_dsi_if == LCD_DSI_IF_BURST_MODE)) {
        u32 dsi_hsa, dsi_hact, dsi_hbp, dsi_hfp, dsi_hblk, dsi_vblk;
        u32 tmp;
        u32 vc = 0;
        u32 x = panel->lcd_x;
        u32 y = panel->lcd_y;
        u32 vt = panel->lcd_vt;
        u32 vbp = panel->lcd_vbp;
        u32 vspw = panel->lcd_vspw;
        u32 ht = panel->lcd_ht;
        u32 hbp = panel->lcd_hbp;
        u32 hspw = panel->lcd_hspw;
        u32 format = panel->lcd_dsi_format;
        u32 lane = panel->lcd_dsi_lane;

        if (panel->lcd_dsi_if == LCD_DSI_IF_BURST_MODE) {
            hspw = 0;
            hbp = 0;
            dsi_hsa = 0;
            dsi_hbp = 0;
            dsi_hact = x * dsi_pixel_bits[format] / 8;
            dsi_hblk = dsi_hact;
            dsi_hfp = 0;
            dsi_vblk = 0;
            dsi_dev[sel]->dsi_basic_ctl.bits.hsa_hse_dis = 1;
            dsi_dev[sel]->dsi_basic_ctl.bits.hbp_dis = 1;
        } else {
            dsi_hsa =
                hspw * dsi_pixel_bits[format] / 8 - (4 + 4 + 2);
            dsi_hbp = (hbp - hspw) * dsi_pixel_bits[format] / 8
                - (4 + 2);
            dsi_hact = x * dsi_pixel_bits[format] / 8;
            dsi_hblk = (ht - hspw) * dsi_pixel_bits[format] / 8
                - (4 + 4 + 2);
            dsi_hfp = dsi_hblk - (4 + dsi_hact + 2)
                - (4 + dsi_hbp + 2);

            if (lane == 4) {
                tmp = (ht * dsi_pixel_bits[format] / 8) * vt
                    - (4 + dsi_hblk + 2);
                dsi_vblk = (lane - tmp % lane);
            } else {
                dsi_vblk = 0;
            }
        }

        dsi_dev[sel]->dsi_sync_hss.bits.vc = vc;
        dsi_dev[sel]->dsi_sync_hss.bits.dt = DSI_DT_HSS;
        dsi_dev[sel]->dsi_sync_hss.bits.d0 = 0;
        dsi_dev[sel]->dsi_sync_hss.bits.d1 = 0;
        dsi_dev[sel]->dsi_sync_hss.bits.ecc =
            dsi_ecc_pro(dsi_dev[sel]->dsi_sync_hss.dwval);
        dsi_dev[sel]->dsi_sync_hse.bits.vc = vc;
        dsi_dev[sel]->dsi_sync_hse.bits.dt = DSI_DT_HSE;
        dsi_dev[sel]->dsi_sync_hse.bits.d0 = 0;
        dsi_dev[sel]->dsi_sync_hse.bits.d1 = 0;
        dsi_dev[sel]->dsi_sync_hse.bits.ecc =
            dsi_ecc_pro(dsi_dev[sel]->dsi_sync_hse.dwval);
        dsi_dev[sel]->dsi_sync_vss.bits.vc = vc;
        dsi_dev[sel]->dsi_sync_vss.bits.dt = DSI_DT_VSS;
        dsi_dev[sel]->dsi_sync_vss.bits.d0 = 0;
        dsi_dev[sel]->dsi_sync_vss.bits.d1 = 0;
        dsi_dev[sel]->dsi_sync_vss.bits.ecc =
            dsi_ecc_pro(dsi_dev[sel]->dsi_sync_vss.dwval);
        dsi_dev[sel]->dsi_sync_vse.bits.vc = vc;
        dsi_dev[sel]->dsi_sync_vse.bits.dt = DSI_DT_VSE;
        dsi_dev[sel]->dsi_sync_vse.bits.d0 = 0;
        dsi_dev[sel]->dsi_sync_vse.bits.d1 = 0;
        dsi_dev[sel]->dsi_sync_vse.bits.ecc =
            dsi_ecc_pro(dsi_dev[sel]->dsi_sync_vse.dwval);

        dsi_dev[sel]->dsi_basic_size0.bits.vsa = vspw;
        dsi_dev[sel]->dsi_basic_size0.bits.vbp = vbp - vspw;
        dsi_dev[sel]->dsi_basic_size1.bits.vact = y;
        dsi_dev[sel]->dsi_basic_size1.bits.vt = vt;
        dsi_dev[sel]->dsi_blk_hsa0.bits.vc = vc;
        dsi_dev[sel]->dsi_blk_hsa0.bits.dt = DSI_DT_BLK;
        dsi_dev[sel]->dsi_blk_hsa0.bits.wc = dsi_hsa;
        dsi_dev[sel]->dsi_blk_hsa0.bits.ecc =
            dsi_ecc_pro(dsi_dev[sel]->dsi_blk_hsa0.dwval);
        dsi_dev[sel]->dsi_blk_hsa1.bits.pd = 0;
        dsi_dev[sel]->dsi_blk_hsa1.bits.pf =
            dsi_crc_pro_pd_repeat(0, dsi_hsa);
        dsi_dev[sel]->dsi_blk_hbp0.bits.vc = vc;
        dsi_dev[sel]->dsi_blk_hbp0.bits.dt = DSI_DT_BLK;
        dsi_dev[sel]->dsi_blk_hbp0.bits.wc = dsi_hbp;
        dsi_dev[sel]->dsi_blk_hbp0.bits.ecc =
            dsi_ecc_pro(dsi_dev[sel]->dsi_blk_hbp0.dwval);
        dsi_dev[sel]->dsi_blk_hbp1.bits.pd = 0;
        dsi_dev[sel]->dsi_blk_hbp1.bits.pf =
            dsi_crc_pro_pd_repeat(0, dsi_hbp);
        dsi_dev[sel]->dsi_blk_hfp0.bits.vc = vc;
        dsi_dev[sel]->dsi_blk_hfp0.bits.dt = DSI_DT_BLK;
        dsi_dev[sel]->dsi_blk_hfp0.bits.wc = dsi_hfp;
        dsi_dev[sel]->dsi_blk_hfp0.bits.ecc =
            dsi_ecc_pro(dsi_dev[sel]->dsi_blk_hfp0.dwval);
        dsi_dev[sel]->dsi_blk_hfp1.bits.pd = 0;
        dsi_dev[sel]->dsi_blk_hfp1.bits.pf =
            dsi_crc_pro_pd_repeat(0, dsi_hfp);
        dsi_dev[sel]->dsi_blk_hblk0.bits.dt = DSI_DT_BLK;
        dsi_dev[sel]->dsi_blk_hblk0.bits.wc = dsi_hblk;
        dsi_dev[sel]->dsi_blk_hblk0.bits.ecc =
            dsi_ecc_pro(dsi_dev[sel]->dsi_blk_hblk0.dwval);
        dsi_dev[sel]->dsi_blk_hblk1.bits.pd = 0;
        dsi_dev[sel]->dsi_blk_hblk1.bits.pf =
            dsi_crc_pro_pd_repeat(0, dsi_hblk);
        dsi_dev[sel]->dsi_blk_vblk0.bits.dt = DSI_DT_BLK;
        dsi_dev[sel]->dsi_blk_vblk0.bits.wc = dsi_vblk;
        dsi_dev[sel]->dsi_blk_vblk0.bits.ecc =
            dsi_ecc_pro(dsi_dev[sel]->dsi_blk_vblk0.dwval);
        dsi_dev[sel]->dsi_blk_vblk1.bits.pd = 0;
        dsi_dev[sel]->dsi_blk_vblk1.bits.pf =
            dsi_crc_pro_pd_repeat(0, dsi_vblk);
    }
    return 0;
}

s32 dsi_cfg(u32 sel, struct disp_panel_para *panel)
{
    dsi_basic_cfg(sel, panel);
    dsi_packet_cfg(sel, panel);
    dsi_dphy_cfg(sel, panel);
    return 0;
}

s32 dsi_exit(u32 sel)
{
    return 0;
}

u8 dsi_ecc_pro(u32 dsi_ph)
{
    union dsi_ph_t ph;

    ph.bytes.byte012 = dsi_ph;

    ph.bits.bit29 =
        ph.bits.bit10 ^ ph.bits.bit11 ^ ph.bits.bit12 ^ ph.bits.bit13 ^ ph.
        bits.bit14 ^ ph.bits.bit15 ^ ph.bits.bit16 ^ ph.bits.bit17 ^ ph.
        bits.bit18 ^ ph.bits.bit19 ^ ph.bits.bit21 ^ ph.bits.bit22 ^ ph.
        bits.bit23;
    ph.bits.bit28 =
        ph.bits.bit04 ^ ph.bits.bit05 ^ ph.bits.bit06 ^ ph.bits.bit07 ^ ph.
        bits.bit08 ^ ph.bits.bit09 ^ ph.bits.bit16 ^ ph.bits.bit17 ^ ph.
        bits.bit18 ^ ph.bits.bit19 ^ ph.bits.bit20 ^ ph.bits.bit22 ^ ph.
        bits.bit23;
    ph.bits.bit27 =
        ph.bits.bit01 ^ ph.bits.bit02 ^ ph.bits.bit03 ^ ph.bits.bit07 ^ ph.
        bits.bit08 ^ ph.bits.bit09 ^ ph.bits.bit13 ^ ph.bits.bit14 ^ ph.
        bits.bit15 ^ ph.bits.bit19 ^ ph.bits.bit20 ^ ph.bits.bit21 ^ ph.
        bits.bit23;
    ph.bits.bit26 =
        ph.bits.bit00 ^ ph.bits.bit02 ^ ph.bits.bit03 ^ ph.bits.bit05 ^ ph.
        bits.bit06 ^ ph.bits.bit09 ^ ph.bits.bit11 ^ ph.bits.bit12 ^ ph.
        bits.bit15 ^ ph.bits.bit18 ^ ph.bits.bit20 ^ ph.bits.bit21 ^ ph.
        bits.bit22;
    ph.bits.bit25 =
        ph.bits.bit00 ^ ph.bits.bit01 ^ ph.bits.bit03 ^ ph.bits.bit04 ^ ph.
        bits.bit06 ^ ph.bits.bit08 ^ ph.bits.bit10 ^ ph.bits.bit12 ^ ph.
        bits.bit14 ^ ph.bits.bit17 ^ ph.bits.bit20 ^ ph.bits.bit21 ^ ph.
        bits.bit22 ^ ph.bits.bit23;
    ph.bits.bit24 =
        ph.bits.bit00 ^ ph.bits.bit01 ^ ph.bits.bit02 ^ ph.bits.bit04 ^ ph.
        bits.bit05 ^ ph.bits.bit07 ^ ph.bits.bit10 ^ ph.bits.bit11 ^ ph.
        bits.bit13 ^ ph.bits.bit16 ^ ph.bits.bit20 ^ ph.bits.bit21 ^ ph.
        bits.bit22 ^ ph.bits.bit23;
    return ph.bytes.byte3;
}

u16 dsi_crc_pro(u8 *pd_p, u32 pd_bytes)
{
    u16 gen_code = 0x8408;
    u16 byte_cntr;
    u8 bit_cntr;
    u8 curr_data;
    u16 crc = 0xffff;

    if (pd_bytes > 0) {
        for (byte_cntr = 0; byte_cntr < pd_bytes; byte_cntr++) {
            curr_data = *(pd_p + byte_cntr);
            for (bit_cntr = 0; bit_cntr < 8; bit_cntr++) {
                if (((crc & 0x0001) ^
                     ((0x0001 * curr_data) & 0x0001)) > 0)
                    crc = ((crc >> 1) & 0x7fff) ^ gen_code;
                else
                    crc = (crc >> 1) & 0x7fff;
                curr_data = (curr_data >> 1) & 0x7f;
            }
        }
    }
    return crc;
}

u16 dsi_crc_pro_pd_repeat(u8 pd, u32 pd_bytes)
{
    u16 gen_code = 0x8408;
    u16 byte_cntr;
    u8 bit_cntr;
    u8 curr_data;
    u16 crc = 0xffff;

    if (pd_bytes > 0) {
        for (byte_cntr = 0; byte_cntr < pd_bytes; byte_cntr++) {
            curr_data = pd;
            for (bit_cntr = 0; bit_cntr < 8; bit_cntr++) {
                if (((crc & 0x0001) ^
                     ((0x0001 * curr_data) & 0x0001)) > 0)
                    crc = ((crc >> 1) & 0x7fff) ^ gen_code;
                else
                    crc = (crc >> 1) & 0x7fff;
                curr_data = (curr_data >> 1) & 0x7f;
            }
        }
    }
    return crc;
}

/**
 * @name       :dsi_read_mode_en
 * @brief      :Enable dsi read mode in the case of reading in display
 * interrupt.
 *  user must enable read mode before read and disable it after read
 * @param[IN]  :sel:dsi module index
 * @param[IN]  :en: enable read mode
 * @return     :none
 */
void dsi_read_mode_en(u32 sel, u32 en)
{
    dsi_dev[sel]->dsi_inst_jump_cfg[0].bits.jump_cfg_en = en;
    if (!en)
        dsi_start(sel, DSI_START_HSTX);
}

#endif
