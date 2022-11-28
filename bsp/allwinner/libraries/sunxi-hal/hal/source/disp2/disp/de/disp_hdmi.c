/*
 * Allwinner SoCs display driver.
 *
 * Copyright (c) 2007-2017 Allwinnertech Co., Ltd.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include "disp_hdmi.h"

#if defined(SUPPORT_HDMI)
struct disp_device_private_data {
    u32 enabled;
    bool hpd;
    bool suspended;

    struct disp_device_config config;

    struct disp_device_func hdmi_func;
    struct disp_video_timings *video_info;

    u32                       frame_per_sec;
    u32                       usec_per_line;
    u32                       judge_line;

    u32 irq_no;

    struct clk *clk;
    struct clk *parent_clk;
};

static u32 hdmi_used;

#if defined(__LINUX_PLAT__)
static spinlock_t hdmi_data_lock;
static struct mutex hdmi_mlock;
#else
static int hdmi_data_lock;
static int hdmi_mlock;
#endif

static struct disp_device *hdmis;
static struct disp_device_private_data *hdmi_private;
s32 disp_hdmi_set_mode(struct disp_device *hdmi, u32 mode);
s32 disp_hdmi_enable(struct disp_device *hdmi);

struct disp_device *disp_get_hdmi(u32 disp)
{
    u32 num_screens;

    num_screens = bsp_disp_feat_get_num_screens();
    if (disp >= num_screens
        || !bsp_disp_feat_is_supported_output_types(disp,
        DISP_OUTPUT_TYPE_HDMI)) {
        DE_WRN("disp %d not support HDMI output\n", disp);
        return NULL;
    }

    return &hdmis[disp];
}

static struct disp_device_private_data *disp_hdmi_get_priv(struct disp_device
                               *hdmi)
{
    if (hdmi == NULL) {
        DE_WRN("NULL hdl!\n");
        return NULL;
    }

    return (struct disp_device_private_data *)hdmi->priv_data;
}

static s32 hdmi_clk_init(struct disp_device *hdmi)
{
    struct disp_device_private_data *hdmip = disp_hdmi_get_priv(hdmi);

    if (!hdmi || !hdmip) {
        DE_WRN("hdmi clk init null hdl!\n");
        return DIS_FAIL;
    }

    if (hdmip->clk) {
        hdmip->parent_clk = clk_get_parent(hdmip->clk);
        if (IS_ERR_OR_NULL(hdmip->parent_clk))
            DE_WRN("get hdmi clk parent fail\n");
    }

    return 0;
}

static s32 hdmi_clk_exit(struct disp_device *hdmi)
{
    struct disp_device_private_data *hdmip = disp_hdmi_get_priv(hdmi);

    if (!hdmi || !hdmip) {
        DE_WRN("hdmi clk init null hdl!\n");
        return DIS_FAIL;
    }

    return 0;
}

bool hdmi_is_divide_by(unsigned long dividend,
                   unsigned long divisor)
{
    bool divide = false;
    unsigned long temp;

    if (divisor == 0)
        goto exit;

    temp = dividend / divisor;
    if (dividend == (temp * divisor))
        divide = true;
exit:
    return divide;
}

static s32 hdmi_clk_config(struct disp_device *hdmi)
{
    struct disp_device_private_data *hdmip = disp_hdmi_get_priv(hdmi);
    struct clk *parent_clk;
    unsigned long rate = 0, round_rate = 0;
    long rate_diff = 0;
    unsigned long parent_rate = 0, parent_round_rate = 0;
    long parent_rate_diff = 0;
    unsigned int div = 1;

    if (!hdmi || !hdmip) {
        DE_WRN("hdmi clk init null hdl!\n");
        return DIS_FAIL;
    }

    parent_clk =  clk_get_parent(hdmip->clk);
    if (!parent_clk) {
        DE_WRN("can not get hdmi prent clk!\n");
        return DIS_FAIL;
    }
    clk_set_rate(parent_clk, 594000000);

    /*calculate rate*/
    rate = hdmip->video_info->pixel_clk * (hdmip->video_info->pixel_repeat + 1);
    if (hdmip->config.format == DISP_CSC_TYPE_YUV420)
        rate /= 2;

    round_rate = clk_round_rate(hdmip->clk, rate);
    rate_diff = (long)(round_rate - rate);
    if ((rate_diff > 5000000) || (rate_diff < -5000000)) {
        for (div = 1; (rate * div) <= 600000000; div++) {
            parent_rate = rate * div;
            parent_round_rate = clk_round_rate(parent_clk,
                               parent_rate);
            parent_rate_diff = (long)(parent_round_rate - parent_rate);
            if ((parent_rate_diff < 5000000)
                && (parent_rate_diff > -5000000)) {
                clk_set_rate(parent_clk, parent_rate);
                clk_set_rate(hdmip->clk, rate);
                break;
            }
        }
        if ((rate * div) > 600000000)
            clk_set_rate(hdmip->clk, rate);
    } else {
        clk_set_rate(hdmip->clk, rate);
    }

    return 0;
}

static s32 hdmi_clk_enable(struct disp_device *hdmi)
{
    struct disp_device_private_data *hdmip = disp_hdmi_get_priv(hdmi);
    int ret = 0;

    if (!hdmi || !hdmip) {
        DE_WRN("hdmi clk init null hdl!\n");
        return DIS_FAIL;
    }

    hdmi_clk_config(hdmi);
    if (hdmip->clk && (!__clk_get_enable_count(hdmip->clk))) {
        ret = clk_prepare_enable(hdmip->clk);
        if (ret != 0)
            DE_WRN("fail enable hdmi's clock!\n");
    }

    return ret;
}

static s32 hdmi_clk_disable(struct disp_device *hdmi)
{
    struct disp_device_private_data *hdmip = disp_hdmi_get_priv(hdmi);

    if (!hdmi || !hdmip) {
        DE_WRN("hdmi clk init null hdl!\n");
        return DIS_FAIL;
    }

    if (hdmip->clk && (__clk_get_enable_count(hdmip->clk)))
        clk_disable_unprepare(hdmip->clk);

    return 0;
}

void disp_hdmi_pad_sel(unsigned int pad_sel)
{
#ifdef USE_CEC_DDC_PAD
    struct disp_device_private_data *hdmip
                = disp_hdmi_get_priv(hdmis);
    if (!hdmis)
        return;
    if (!hdmip->clk)
        return;
    if (!__clk_get_enable_count(hdmip->clk))
        clk_prepare_enable(hdmip->clk);
    disp_al_hdmi_pad_sel(hdmis->hwdev_index, pad_sel);
#endif
}
EXPORT_SYMBOL(disp_hdmi_pad_sel);

void disp_hdmi_pad_release(void)
{
#ifdef USE_CEC_DDC_PAD
    struct disp_device_private_data *hdmip
                = disp_hdmi_get_priv(hdmis);
    if (!hdmis)
        return;

    disp_al_hdmi_pad_sel(hdmis->hwdev_index, 0);

    if (!hdmip->clk)
        return;

    if (__clk_get_enable_count(hdmip->clk))
        clk_disable_unprepare(hdmip->clk);
#endif
}
EXPORT_SYMBOL(disp_hdmi_pad_release);

static s32 hdmi_calc_judge_line(struct disp_device *hdmi)
{
    struct disp_device_private_data *hdmip = disp_hdmi_get_priv(hdmi);
    int start_delay, usec_start_delay;
    int usec_judge_point;
    u64 temp;

    if ((hdmi == NULL) || (hdmip == NULL)) {
        DE_WRN("null  hdl!\n");
        return DIS_FAIL;
    }

    /*
     * usec_per_line = 1 / fps / vt * 1000000
     *               = 1 / (pixel_clk / vt / ht) / vt * 1000000
     *               = ht / pixel_clk * 1000000
     */
    hdmip->frame_per_sec = hdmip->video_info->pixel_clk
        / hdmip->video_info->hor_total_time
        / hdmip->video_info->ver_total_time
        * (hdmip->video_info->b_interlace + 1)
        / (hdmip->video_info->trd_mode + 1);

    temp = hdmip->video_info->hor_total_time * 1000000ull;
    do_div(temp, hdmip->video_info->pixel_clk);
    hdmip->usec_per_line = temp;

    start_delay = disp_al_device_get_start_delay(hdmi->hwdev_index);
    usec_start_delay = start_delay * hdmip->usec_per_line;

    if (usec_start_delay <= 200)
        usec_judge_point = usec_start_delay * 3 / 7;
    else if (usec_start_delay <= 400)
        usec_judge_point = usec_start_delay / 2;
    else
        usec_judge_point = 200;
    hdmip->judge_line = usec_judge_point / hdmip->usec_per_line;

    return 0;
}

static s32 disp_hdmi_set_func(struct disp_device *hdmi,
                  struct disp_device_func *func)
{
    struct disp_device_private_data *hdmip = disp_hdmi_get_priv(hdmi);

    if ((hdmi == NULL) || (hdmip == NULL)) {
        DE_WRN("hdmi set func null  hdl!\n");
        return DIS_FAIL;
    }

    memcpy(&hdmip->hdmi_func, func, sizeof(struct disp_device_func));

    return 0;
}

#if defined(__LINUX_PLAT__)
static s32 disp_hdmi_event_proc(int irq, void *parg)
#else
static s32 disp_hdmi_event_proc(void *parg)
#endif
{
    struct disp_device *hdmi = (struct disp_device *)parg;
    struct disp_manager *mgr = NULL;
    u32 hwdev_index;

    if (hdmi == NULL)
        return DISP_IRQ_RETURN;

    hwdev_index = hdmi->hwdev_index;

    if (disp_al_device_query_irq(hwdev_index)) {
        int cur_line = disp_al_device_get_cur_line(hwdev_index);
        int start_delay = disp_al_device_get_start_delay(hwdev_index);

        mgr = hdmi->manager;
        if (mgr == NULL)
            return DISP_IRQ_RETURN;

        if (cur_line <= (start_delay - 4))
            sync_event_proc(mgr->disp, false);
        else
            sync_event_proc(mgr->disp, true);
    }

    return DISP_IRQ_RETURN;
}

static s32 disp_hdmi_init(struct disp_device *hdmi)
{
    struct disp_device_private_data *hdmip = disp_hdmi_get_priv(hdmi);

    if (!hdmi || !hdmip) {
        DE_WRN("hdmi init null hdl!\n");
        return DIS_FAIL;
    }

    hdmi_clk_init(hdmi);

    return 0;
}

static s32 disp_hdmi_exit(struct disp_device *hdmi)
{
    struct disp_device_private_data *hdmip = disp_hdmi_get_priv(hdmi);

    if (!hdmi || !hdmip) {
        DE_WRN("hdmi init null hdl!\n");
        return DIS_FAIL;
    }

    hdmi_clk_exit(hdmi);

    return 0;
}

static s32 cal_real_frame_period(struct disp_device *hdmi)
{
    s32 ret = -1;
    struct disp_device_private_data *hdmip;
    unsigned long long temp = 0;

    if (!hdmi) {
        DE_WRN("hdmi is null!\n");
        goto OUT;
    }

    hdmip = disp_hdmi_get_priv(hdmi);

    if (!hdmip) {
        DE_WRN("hdmip is null!\n");
        goto OUT;
    }

    if (!hdmip->clk || !hdmip->video_info) {
        DE_WRN("hdmi clk | video_info null!\n");
        goto OUT;
    }

    hdmi->timings.dclk_rate_set = clk_get_rate(hdmip->clk);

    if (!hdmi->timings.dclk_rate_set) {
        DE_WRN("hdmi dclk_rate_set is 0!\n");
        goto OUT;
    }

    temp = ONE_SEC * hdmip->video_info->hor_total_time *
           hdmip->video_info->ver_total_time *
           (hdmip->video_info->pixel_repeat + 1);

    do_div(temp, hdmi->timings.dclk_rate_set *
             (hdmip->video_info->b_interlace + 1));

    hdmi->timings.frame_period = temp;

    DE_INF("hdmi frame period:%llu\n", hdmi->timings.frame_period);

    hdmi->timings.start_delay =
        disp_al_device_get_start_delay(hdmi->hwdev_index);
    ret = 0;
OUT:
    return ret;
}

s32 disp_hdmi_enable(struct disp_device *hdmi)
{
    unsigned long flags;
    struct disp_device_private_data *hdmip = disp_hdmi_get_priv(hdmi);
    struct disp_manager *mgr = NULL;
    int ret;

    if ((hdmi == NULL) || (hdmip == NULL)) {
        DE_WRN("hdmi set func null  hdl!\n");
        return DIS_FAIL;
    }
    DE_INF("%s, disp%d\n", __func__, hdmi->disp);

    if (hdmip->enabled == 1) {
        DE_WRN("hdmi%d is already enable\n", hdmi->disp);
        return DIS_FAIL;
    }

    mgr = hdmi->manager;
    if (!mgr) {
        DE_WRN("hdmi%d's mgr is NULL\n", hdmi->disp);
        return DIS_FAIL;
    }

    if (hdmip->hdmi_func.get_video_timing_info == NULL) {
        DE_WRN("hdmi_get_video_timing_info func is null\n");
        return DIS_FAIL;
    }

    hdmip->hdmi_func.get_video_timing_info(&(hdmip->video_info));

    if (hdmip->video_info == NULL) {
        DE_WRN("video info is null\n");
        return DIS_FAIL;
    }
    mutex_lock(&hdmi_mlock);
    if (hdmip->enabled == 1)
        goto exit;
    memcpy(&hdmi->timings, hdmip->video_info,
           sizeof(struct disp_video_timings));
    hdmi_calc_judge_line(hdmi);

    if (mgr->enable)
        mgr->enable(mgr);

    disp_sys_register_irq(hdmip->irq_no, 0, disp_hdmi_event_proc,
                  (void *)hdmi, 0, 0);
    disp_sys_enable_irq(hdmip->irq_no);

    ret = hdmi_clk_enable(hdmi);
    if (ret != 0)
        goto exit;

    ret = cal_real_frame_period(hdmi);
    if (ret)
        DE_WRN("cal_real_frame_period fail\n");

    disp_al_hdmi_cfg(hdmi->hwdev_index, hdmip->video_info);
    disp_al_hdmi_enable(hdmi->hwdev_index);

    if (hdmip->hdmi_func.enable != NULL)
        hdmip->hdmi_func.enable();
    else
        DE_WRN("hdmi_open is NULL\n");

    spin_lock_irqsave(&hdmi_data_lock, flags);
    hdmip->enabled = 1;
    spin_unlock_irqrestore(&hdmi_data_lock, flags);

exit:
    mutex_unlock(&hdmi_mlock);

    return 0;
}

static s32 disp_hdmi_sw_enable(struct disp_device *hdmi)
{
    unsigned long flags;
    struct disp_device_private_data *hdmip = disp_hdmi_get_priv(hdmi);
    struct disp_manager *mgr = NULL;

    if ((hdmi == NULL) || (hdmip == NULL)) {
        DE_WRN("hdmi set func null  hdl!\n");
        return DIS_FAIL;
    }
    mgr = hdmi->manager;
    if (!mgr) {
        DE_WRN("hdmi%d's mgr is NULL\n", hdmi->disp);
        return DIS_FAIL;
    }

    if (hdmip->hdmi_func.get_video_timing_info == NULL) {
        DE_WRN("hdmi_get_video_timing_info func is null\n");
        return DIS_FAIL;
    }

    hdmip->hdmi_func.get_video_timing_info(&(hdmip->video_info));

    if (hdmip->video_info == NULL) {
        DE_WRN("video info is null\n");
        return DIS_FAIL;
    }
    mutex_lock(&hdmi_mlock);
    memcpy(&hdmi->timings, hdmip->video_info,
           sizeof(struct disp_video_timings));
    hdmi_calc_judge_line(hdmi);

    if (mgr->sw_enable)
        mgr->sw_enable(mgr);

    disp_al_hdmi_irq_disable(hdmi->hwdev_index);
    disp_sys_register_irq(hdmip->irq_no, 0, disp_hdmi_event_proc,
                  (void *)hdmi, 0, 0);
    disp_sys_enable_irq(hdmip->irq_no);
    disp_al_hdmi_irq_enable(hdmi->hwdev_index);

#if !defined(CONFIG_COMMON_CLK_ENABLE_SYNCBOOT)
    if (hdmi_clk_enable(hdmi) != 0)
        return -1;
#endif

    if (0 != cal_real_frame_period(hdmi))
        DE_WRN("cal_real_frame_period fail\n");

    spin_lock_irqsave(&hdmi_data_lock, flags);
    hdmip->enabled = 1;
    spin_unlock_irqrestore(&hdmi_data_lock, flags);
    mutex_unlock(&hdmi_mlock);

    return 0;
}

static s32 disp_hdmi_disable(struct disp_device *hdmi)
{
    struct disp_device_private_data *hdmip = disp_hdmi_get_priv(hdmi);
    unsigned long flags;
    struct disp_manager *mgr = NULL;

    if ((hdmi == NULL) || (hdmip == NULL)) {
        DE_WRN("hdmi set func null  hdl!\n");
        return DIS_FAIL;
    }

    mgr = hdmi->manager;
    if (!mgr) {
        DE_WRN("hdmi%d's mgr is NULL\n", hdmi->disp);
        return DIS_FAIL;
    }

    if (hdmip->enabled == 0) {
        DE_WRN("hdmi%d is already disable\n", hdmi->disp);
        return DIS_FAIL;
    }

    if (hdmip->hdmi_func.disable == NULL)
        return -1;

    mutex_lock(&hdmi_mlock);
    if (hdmip->enabled == 0)
        goto exit;

    spin_lock_irqsave(&hdmi_data_lock, flags);
    hdmip->enabled = 0;
    spin_unlock_irqrestore(&hdmi_data_lock, flags);

    hdmip->hdmi_func.disable();

    disp_al_hdmi_disable(hdmi->hwdev_index);
    hdmi_clk_disable(hdmi);

    if (mgr->disable)
        mgr->disable(mgr);

    disp_sys_disable_irq(hdmip->irq_no);
    disp_sys_unregister_irq(hdmip->irq_no, disp_hdmi_event_proc,
                (void *)hdmi);

exit:
    mutex_unlock(&hdmi_mlock);

    return 0;
}

static s32 disp_hdmi_is_enabled(struct disp_device *hdmi)
{
    struct disp_device_private_data *hdmip = disp_hdmi_get_priv(hdmi);

    if ((hdmi == NULL) || (hdmip == NULL)) {
        DE_WRN("null hdl!\n");
        return DIS_FAIL;
    }

    return hdmip->enabled;
}


s32 disp_hdmi_set_mode(struct disp_device *hdmi, u32 mode)
{
    s32 ret = 0;
    struct disp_device_private_data *hdmip = disp_hdmi_get_priv(hdmi);

    if ((NULL == hdmi) || (NULL == hdmip)) {
        DE_WRN("hdmi set func null  hdl!\n");
        return DIS_FAIL;
    }

    if (hdmip->hdmi_func.set_mode == NULL) {
        DE_WRN("hdmi_set_mode is null!\n");
        return -1;
    }

    ret = hdmip->hdmi_func.set_mode((enum disp_tv_mode)mode);

    if (ret == 0)
        hdmip->config.mode = mode;

    return ret;
}

static s32 disp_hdmi_get_mode(struct disp_device *hdmi)
{
    struct disp_device_private_data *hdmip = disp_hdmi_get_priv(hdmi);

    if ((NULL == hdmi) || (NULL == hdmip)) {
        DE_WRN("hdmi set func null  hdl!\n");
        return DIS_FAIL;
    }

    return hdmip->config.mode;
}

static s32 disp_hdmi_detect(struct disp_device *hdmi)
{
    struct disp_device_private_data *hdmip = disp_hdmi_get_priv(hdmi);

    if ((NULL == hdmi) || (NULL == hdmip)) {
        DE_WRN("hdmi set func null  hdl!\n");
        return DIS_FAIL;
    }
    if (hdmip->hdmi_func.get_HPD_status)
        return hdmip->hdmi_func.get_HPD_status();
    return DIS_FAIL;
}

static s32 disp_hdmi_set_detect(struct disp_device *hdmi, bool hpd)
{
    struct disp_device_private_data *hdmip = disp_hdmi_get_priv(hdmi);
    struct disp_manager *mgr = NULL;

    if ((NULL == hdmi) || (NULL == hdmip)) {
        DE_WRN("hdmi set func null  hdl!\n");
        return DIS_FAIL;
    }
    mgr = hdmi->manager;
    if (!mgr)
        return DIS_FAIL;

    mutex_lock(&hdmi_mlock);
    if ((1 == hdmip->enabled) && (true == hpd)) {
        if (hdmip->hdmi_func.get_video_timing_info) {
            hdmip->hdmi_func.get_video_timing_info(
                            &(hdmip->video_info));
            if (hdmip->video_info == NULL) {
                DE_WRN("video info is null\n");
                hdmip->hpd = hpd;
                mutex_unlock(&hdmi_mlock);
                return DIS_FAIL;
            }
        }

        if (mgr->update_color_space)
            mgr->update_color_space(mgr);
    }
    hdmip->hpd = hpd;
    mutex_unlock(&hdmi_mlock);

    return 0;
}

static s32 disp_hdmi_smooth_enable(struct disp_device *hdmi)
{
    struct disp_device_private_data *hdmip = disp_hdmi_get_priv(hdmi);
    struct disp_manager *mgr = NULL;

    if ((NULL == hdmi) || (NULL == hdmip)) {
        DE_WRN("hdmi set func null  hdl!\n");
        return DIS_FAIL;
    }
    mgr = hdmi->manager;
    if (!mgr)
        return DIS_FAIL;

    mutex_lock(&hdmi_mlock);
    if (mgr->smooth_switch)
        mgr->smooth_switch(mgr);
    if (hdmip->hdmi_func.smooth_enable)
        hdmip->hdmi_func.smooth_enable();
    mutex_unlock(&hdmi_mlock);

    return 0;
}

static s32 disp_hdmi_check_support_mode(struct disp_device *hdmi, u32 mode)
{
    struct disp_device_private_data *hdmip = disp_hdmi_get_priv(hdmi);

    if ((NULL == hdmi) || (NULL == hdmip)) {
        DE_WRN("hdmi set func null  hdl!\n");
        return DIS_FAIL;
    }

    if (hdmip->hdmi_func.mode_support == NULL)
        return -1;

    return hdmip->hdmi_func.mode_support(mode);
}

static s32 disp_hdmi_get_input_csc(struct disp_device *hdmi)
{
    struct disp_device_private_data *hdmip = disp_hdmi_get_priv(hdmi);

    if ((NULL == hdmi) || (NULL == hdmip)) {
        DE_WRN("hdmi set func null  hdl!\n");
        return 0;
    }

    if (hdmip->hdmi_func.get_input_csc == NULL)
        return 0;

    return hdmip->hdmi_func.get_input_csc();
}

static s32 disp_hdmi_get_input_color_range(struct disp_device *hdmi)
{
    struct disp_device_private_data *hdmip = disp_hdmi_get_priv(hdmi);
    if ((NULL == hdmi) || (NULL == hdmip)) {
        DE_WRN("hdmi set func null  hdl!\n");
        return DIS_FAIL;
    }

    if (hdmip->hdmi_func.get_input_color_range)
        return hdmip->hdmi_func.get_input_color_range();

    if (0 == disp_hdmi_get_input_csc(hdmi))
        return DISP_COLOR_RANGE_0_255;
    else
        return DISP_COLOR_RANGE_16_235;
}

static s32 disp_hdmi_cec_standby_request(struct disp_device *hdmi)
{
    struct disp_device_private_data *hdmip = disp_hdmi_get_priv(hdmi);

    if ((NULL == hdmi) || (NULL == hdmip)) {
        DE_WRN("hdmi set func null  hdl!\n");
        return DIS_FAIL;
    }

    if (hdmip->hdmi_func.cec_standby_request == NULL)
        return -1;

    return hdmip->hdmi_func.cec_standby_request();
}

static s32 disp_hdmi_cec_send_one_touch_play(struct disp_device *hdmi)
{
    struct disp_device_private_data *hdmip = disp_hdmi_get_priv(hdmi);

    if ((NULL == hdmi) || (NULL == hdmip)) {
        DE_WRN("hdmi set func null  hdl!\n");
        return DIS_FAIL;
    }

    if (hdmip->hdmi_func.cec_send_one_touch_play == NULL)
        return -1;

    return hdmip->hdmi_func.cec_send_one_touch_play();
}

static s32 disp_hdmi_suspend(struct disp_device *hdmi)
{
    struct disp_device_private_data *hdmip = disp_hdmi_get_priv(hdmi);

    if ((NULL == hdmi) || (NULL == hdmip)) {
        DE_WRN("hdmi set func null  hdl!\n");
        return DIS_FAIL;
    }

    mutex_lock(&hdmi_mlock);
    if (false == hdmip->suspended) {
        if (hdmip->hdmi_func.suspend != NULL)
            hdmip->hdmi_func.suspend();

        hdmip->suspended = true;
    }
    mutex_unlock(&hdmi_mlock);

    return 0;
}

static s32 disp_hdmi_resume(struct disp_device *hdmi)
{
    struct disp_device_private_data *hdmip = disp_hdmi_get_priv(hdmi);

    if ((NULL == hdmi) || (NULL == hdmip)) {
        DE_WRN("hdmi set func null  hdl!\n");
        return DIS_FAIL;
    }

    mutex_lock(&hdmi_mlock);
    if (true == hdmip->suspended) {
        if (hdmip->hdmi_func.resume != NULL)
            hdmip->hdmi_func.resume();

        hdmip->suspended = false;
    }
    mutex_unlock(&hdmi_mlock);

    return 0;
}

static s32 disp_hdmi_get_fps(struct disp_device *hdmi)
{
    struct disp_device_private_data *hdmip = disp_hdmi_get_priv(hdmi);

    if ((NULL == hdmi) || (NULL == hdmip)) {
        DE_WRN("hdmi set func null  hdl!\n");
        return 0;
    }

    return hdmip->frame_per_sec;
}

static disp_config_update_t disp_hdmi_check_config_dirty(struct disp_device *hdmi,
                    struct disp_device_config *config)
{
    int ret = DISP_NOT_UPDATE;
    struct disp_device_private_data *hdmip = disp_hdmi_get_priv(hdmi);

    if ((hdmi == NULL) || (hdmip == NULL) || (config == NULL)) {
        DE_WRN("NULL hdl!\n");
        ret = DISP_NOT_UPDATE;
        goto exit;
    }

    if (config->type != hdmi->type) {
        DE_WRN("something error! type(0x%x) is error\n", config->type);
        ret = DISP_NOT_UPDATE;
        goto exit;
    }

    if (hdmip->enabled == 0) {
        ret = DISP_NORMAL_UPDATE;
        goto exit;
    }

    if (hdmip->hdmi_func.set_static_config == NULL) {
        ret = (config->mode != hdmip->config.mode);
    } else {
        if ((config->mode != hdmip->config.mode) ||
            (config->format != hdmip->config.format) ||
            (config->bits != hdmip->config.bits) ||
            (config->dvi_hdmi != hdmip->config.dvi_hdmi))
            ret = DISP_NORMAL_UPDATE;
        else if ((config->eotf != hdmip->config.eotf) ||
            (config->cs != hdmip->config.cs) ||
            (config->range != hdmip->config.range) ||
            (config->scan != hdmip->config.scan) ||
            (config->aspect_ratio != hdmip->config.aspect_ratio))
            ret = DISP_SMOOTH_UPDATE;
    }

exit:
    return ret;
}

static s32 disp_hdmi_set_static_config(struct disp_device *hdmi,
                   struct disp_device_config *config)
{
    int ret = true;
    struct disp_device_private_data *hdmip = disp_hdmi_get_priv(hdmi);

    if ((hdmi == NULL) || (hdmip == NULL)) {
        DE_WRN("NULL hdl!\n");
        ret = false;
        goto exit;
    }
    if (hdmip->hdmi_func.set_static_config == NULL)
        return disp_hdmi_set_mode(hdmi, config->mode);

    memcpy(&hdmip->config, config, sizeof(struct disp_device_config));
    return hdmip->hdmi_func.set_static_config(config);

exit:
    return ret;
}

static s32 disp_hdmi_get_static_config(struct disp_device *hdmi,
                  struct disp_device_config *config)
{
    int ret = 0;
    struct disp_device_private_data *hdmip = disp_hdmi_get_priv(hdmi);

    if ((hdmi == NULL) || (hdmip == NULL)) {
        DE_WRN("NULL hdl!\n");
        ret = -1;
        goto exit;
    }

    if (hdmip->hdmi_func.set_static_config == NULL) {
        config->type = hdmi->type;
        config->mode = hdmip->config.mode;
        if (hdmip->hdmi_func.get_input_csc == NULL)
            config->format = DISP_CSC_TYPE_YUV444;
        else
            config->format =
                hdmip->hdmi_func.get_input_csc();
        config->bits = DISP_DATA_8BITS;
        config->eotf = DISP_EOTF_GAMMA22;
        if ((hdmi->timings.x_res <= 736) &&
           (hdmi->timings.y_res <= 576))
            config->cs = DISP_BT601_F;
        else
            config->cs = DISP_BT709_F;
    } else {
        memcpy(config,
               &hdmip->config,
               sizeof(struct disp_device_config));
    }

exit:
    return ret;
}

static s32 disp_hdmi_set_dynamic_config(struct disp_device *hdmi,
                   struct disp_device_dynamic_config *config)
{
    int ret = -1;
    struct disp_device_private_data *hdmip = disp_hdmi_get_priv(hdmi);

    if ((hdmi == NULL) || (hdmip == NULL)) {
        DE_WRN("NULL hdl!\n");
        ret = false;
        goto exit;
    }
    if (hdmip->hdmi_func.set_dynamic_config != NULL)
        return hdmip->hdmi_func.set_dynamic_config(config);

exit:
        return ret;
}

s32 disp_init_hdmi(struct disp_bsp_init_para *para)
{
    u32 num_devices;
    u32 disp = 0;
    struct disp_device *hdmi;
    struct disp_device_private_data *hdmip;
    u32 hwdev_index = 0;
    u32 num_devices_support_hdmi = 0;
    char compat[32] = { 0 };
    const char *str;
    struct device_node *node;
    int ret;

    snprintf(compat, sizeof(compat), "allwinner,sunxi-hdmi");
    node = of_find_compatible_node(NULL, NULL, compat);
    if (!node) {
        pr_err("do not get the node of hdmi\n");
        goto exit;
    }

    ret = of_property_read_string(node, "status", &str);
    if (ret || strcmp(str, "okay")) {
        DE_WRN("dont support hdmi\n");
        goto exit;
    }
    hdmi_used = 1;

    DE_INF("disp_init_hdmi\n");

    spin_lock_init(&hdmi_data_lock);
    mutex_init(&hdmi_mlock);

    num_devices = bsp_disp_feat_get_num_devices();
    for (hwdev_index = 0; hwdev_index < num_devices; hwdev_index++) {
        if (bsp_disp_feat_is_supported_output_types(hwdev_index,
            DISP_OUTPUT_TYPE_HDMI))
            num_devices_support_hdmi++;
    }
    hdmis =
        kmalloc_array(num_devices_support_hdmi,
              sizeof(struct disp_device),
              GFP_KERNEL | __GFP_ZERO);
    if (hdmis == NULL) {
        DE_WRN("malloc memory fail!\n");
        goto malloc_err;
    }

    hdmi_private =
        (struct disp_device_private_data *)
        kmalloc(sizeof(struct disp_device_private_data)
            * num_devices_support_hdmi,
            GFP_KERNEL | __GFP_ZERO);
    if (hdmi_private == NULL) {
        DE_WRN("malloc memory fail!\n");
        goto malloc_err;
    }

    disp = 0;
    for (hwdev_index = 0; hwdev_index < num_devices; hwdev_index++) {
        if (!bsp_disp_feat_is_supported_output_types
            (hwdev_index, DISP_OUTPUT_TYPE_HDMI)) {
            continue;
        }

        hdmi = &hdmis[disp];
        hdmip = &hdmi_private[disp];
        hdmi->priv_data = (void *)hdmip;

        hdmi->disp = disp;
        hdmi->hwdev_index = hwdev_index;
        sprintf(hdmi->name, "hdmi%d", disp);
        hdmi->type = DISP_OUTPUT_TYPE_HDMI;
        hdmip->config.type = DISP_OUTPUT_TYPE_HDMI;
        hdmip->config.mode = DISP_TV_MOD_720P_50HZ;
        hdmip->config.format = DISP_CSC_TYPE_YUV444;
        hdmip->config.bits = DISP_DATA_8BITS;
        hdmip->config.eotf = DISP_EOTF_GAMMA22;
        hdmip->config.cs = DISP_UNDEF;
        hdmip->config.dvi_hdmi = DISP_HDMI;
        hdmip->config.range = DISP_COLOR_RANGE_16_235;
        hdmip->config.scan = DISP_SCANINFO_NO_DATA;
        hdmip->config.aspect_ratio = 8;
        hdmip->irq_no =
            para->irq_no[DISP_MOD_LCD0 + hwdev_index];
        hdmip->clk = para->mclk[DISP_MOD_LCD0 + hwdev_index];

        hdmi->set_manager = disp_device_set_manager;
        hdmi->unset_manager = disp_device_unset_manager;
        hdmi->get_resolution = disp_device_get_resolution;
        hdmi->get_timings = disp_device_get_timings;
        hdmi->is_interlace = disp_device_is_interlace;

        hdmi->init = disp_hdmi_init;
        hdmi->exit = disp_hdmi_exit;

        hdmi->set_func = disp_hdmi_set_func;
        hdmi->enable = disp_hdmi_enable;
        hdmi->sw_enable = disp_hdmi_sw_enable;
        hdmi->disable = disp_hdmi_disable;
        hdmi->is_enabled = disp_hdmi_is_enabled;
        /* hdmi->check_if_enabled = disp_hdmi_check_if_enabled; */
        hdmi->set_mode = disp_hdmi_set_mode;
        hdmi->get_mode = disp_hdmi_get_mode;
        hdmi->check_support_mode = disp_hdmi_check_support_mode;
        hdmi->set_static_config = disp_hdmi_set_static_config;
        hdmi->get_static_config = disp_hdmi_get_static_config;
        hdmi->set_dynamic_config = disp_hdmi_set_dynamic_config;
        hdmi->check_config_dirty = disp_hdmi_check_config_dirty;
        hdmi->get_input_csc = disp_hdmi_get_input_csc;
        hdmi->get_input_color_range =
            disp_hdmi_get_input_color_range;
        hdmi->cec_standby_request =
            disp_hdmi_cec_standby_request;
        hdmi->cec_send_one_touch_play =
            disp_hdmi_cec_send_one_touch_play;
        hdmi->suspend = disp_hdmi_suspend;
        hdmi->resume = disp_hdmi_resume;
        hdmi->detect = disp_hdmi_detect;
        hdmi->set_detect = disp_hdmi_set_detect;
        hdmi->smooth_enable = disp_hdmi_smooth_enable;
        hdmi->get_status = disp_device_get_status;
        hdmi->is_in_safe_period = disp_device_is_in_safe_period;
        hdmi->usec_before_vblank =
            disp_device_usec_before_vblank;
        hdmi->get_fps = disp_hdmi_get_fps;
        hdmi->show_builtin_patten = disp_device_show_builtin_patten;

        hdmi->init(hdmi);
        disp_device_register(hdmi);
        disp++;
    }

    return 0;

malloc_err:
    disp_sys_free(hdmis);
    disp_sys_free(hdmi_private);
    hdmis = NULL;
    hdmi_private = NULL;
exit:
    return -1;
}

s32 disp_exit_hdmi(void)
{
    u32 num_devices;
    u32 disp = 0;
    struct disp_device *hdmi;
    u32 hwdev_index = 0;

    if ((hdmi_used == 0) || (!hdmis))
        return 0;

    num_devices = bsp_disp_feat_get_num_devices();

    disp = 0;
    for (hwdev_index = 0; hwdev_index < num_devices; hwdev_index++) {
        if (!bsp_disp_feat_is_supported_output_types
            (hwdev_index, DISP_OUTPUT_TYPE_HDMI)) {
            continue;
        }

        hdmi = &hdmis[disp];
        disp_device_unregister(hdmi);
        hdmi->exit(hdmi);
        disp++;
    }

    disp_sys_free(hdmis);
    disp_sys_free(hdmi_private);
    hdmis = NULL;
    hdmi_private = NULL;

    return 0;
}
#endif
