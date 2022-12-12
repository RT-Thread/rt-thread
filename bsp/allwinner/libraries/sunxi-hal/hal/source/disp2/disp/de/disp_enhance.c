/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#if defined(CONFIG_DISP2_SUNXI_SUPPORT_ENAHNCE)
#include "disp_enhance.h"
#include <hal_atomic.h>

extern hal_spinlock_t disp_lock;

struct disp_enhance_private_data {
    u32 reg_base;
    u32 enabled;
    bool applied;

    struct disp_enhance_config config;

     s32 (*shadow_protect)(u32 sel, bool protect);
};
static u32 enhance_data_lock;

static struct disp_enhance *enhances;
static struct disp_enhance_private_data *enhance_private;

struct disp_enhance *disp_get_enhance(u32 disp)
{
    u32 num_screens;

    num_screens = bsp_disp_feat_get_num_screens();
    if (disp >= num_screens) {
        DE_WRN("disp %d out of range\n", disp);
        return NULL;
    }

    return &enhances[disp];
}

static struct disp_enhance_private_data *disp_enhance_get_priv(struct
                                   disp_enhance
                                   *enhance)
{
    if (enhance == NULL) {
        DE_INF("NULL hdl!\n");
        return NULL;
    }

    return &enhance_private[enhance->disp];
}

static s32 disp_enhance_sync(struct disp_enhance *enhance)
{
    struct disp_enhance_private_data *enhancep =
        disp_enhance_get_priv(enhance);

    if ((enhance == NULL) || (enhancep == NULL)) {
        DE_INF("NULL hdl!\n");
        return -1;
    }

    enhance->update_regs(enhance);
    if (enhancep->enabled)
        disp_al_enhance_sync(enhance->disp);

    return 0;
}

static s32 disp_enhance_tasklet(struct disp_enhance *enhance)
{
    /* unsigned long flags; */
    struct disp_enhance_private_data *enhancep =
        disp_enhance_get_priv(enhance);

    if ((enhance == NULL) || (enhancep == NULL)) {
        DE_INF("NULL hdl!\n");
        return -1;
    }

    if (enhancep->enabled)
        disp_al_enhance_tasklet(enhance->disp);

    return 0;
}

static s32 disp_enhance_update_regs(struct disp_enhance *enhance)
{
    struct disp_enhance_private_data *enhancep =
        disp_enhance_get_priv(enhance);

    if ((enhance == NULL) || (enhancep == NULL)) {
        DE_INF("NULL hdl!\n");
        return -1;
    }

    /* size likely change while it depend on layer size */
    /* if (enhancep->applied) { */
    {
        disp_al_enhance_update_regs(enhance->disp);
    }

    enhance_data_lock = hal_spin_lock_irqsave(&disp_lock);
    enhancep->applied = false;
    hal_spin_unlock_irqrestore(&disp_lock, enhance_data_lock);

    return 0;
}

static s32 disp_enhance_apply(struct disp_enhance *enhance)
{
    struct disp_enhance_private_data *enhancep =
        disp_enhance_get_priv(enhance);
    struct disp_enhance_config config;

    if ((enhance == NULL) || (enhancep == NULL)) {
        DE_INF("NULL hdl!\n");
        return -1;
    }
    DE_INF("disp_enhance_apply, screen %d\n", enhance->disp);
    memset(&config, 0, sizeof(struct disp_enhance_config));
    enhance_data_lock = hal_spin_lock_irqsave(&disp_lock);
    if (enhancep->config.flags != 0) {
        memcpy(&config, &enhancep->config,
               sizeof(struct disp_enhance_config));
        enhancep->applied = true;
    }
    hal_spin_unlock_irqrestore(&disp_lock, enhance_data_lock);

    if (config.flags != ENH_NONE_DIRTY) {
        disp_enhance_shadow_protect(enhance, 1);
        disp_al_enhance_apply(enhance->disp, &config);
        disp_enhance_shadow_protect(enhance, 0);
    }

    enhance_data_lock = hal_spin_lock_irqsave(&disp_lock);
    if (config.flags != 0)
        enhancep->applied = true;
    config.flags = ENH_NONE_DIRTY;
    hal_spin_unlock_irqrestore(&disp_lock, enhance_data_lock);

    return 0;
}

static s32 disp_enhance_force_apply(struct disp_enhance *enhance)
{
    struct disp_enhance_private_data *enhancep =
        disp_enhance_get_priv(enhance);
    struct disp_device *dispdev = NULL;

    if ((enhance == NULL) || (enhancep == NULL)) {
        DE_INF("NULL hdl!\n");
        return -1;
    }
    if (enhance->manager)
        dispdev = enhance->manager->device;
    if (dispdev)
        dispdev->get_resolution(dispdev,
                    &enhancep->config.info.size.width,
                    &enhancep->config.info.size.height);

    enhance_data_lock = hal_spin_lock_irqsave(&disp_lock);
    enhancep->config.flags |= ENH_ALL_DIRTY;
    hal_spin_unlock_irqrestore(&disp_lock, enhance_data_lock);
    disp_enhance_apply(enhance);
    disp_enhance_update_regs(enhance);
    disp_enhance_sync(enhance);

    return 0;
}

/* seem no meaning */
static bool disp_enhance_is_enabled(struct disp_enhance *enhance)
{
    struct disp_enhance_private_data *enhancep =
        disp_enhance_get_priv(enhance);

    if ((enhance == NULL) || (enhancep == NULL)) {
        DE_INF("NULL hdl!\n");
        return false;
    }

    return enhancep->enabled;
}

static s32 disp_enhance_enable(struct disp_enhance *enhance)
{
    unsigned long flags;
    struct disp_enhance_private_data *enhancep =
        disp_enhance_get_priv(enhance);
    struct disp_device *dispdev = NULL;

    if ((enhance == NULL) || (enhancep == NULL)) {
        DE_INF("NULL hdl!\n");
        return -1;
    }
    if (enhance->manager)
        dispdev = enhance->manager->device;
    if (dispdev) {
        dispdev->get_resolution(dispdev,
                    &enhancep->config.info.size.width,
                    &enhancep->config.info.size.height);
        if (dispdev->type == DISP_OUTPUT_TYPE_HDMI)
            enhancep->config.info.mode = (enhancep->config.info.mode
                & 0xffff0000) | (1);    /* hdmi */
        else
            enhancep->config.info.mode = (enhancep->config.info.mode
                & 0xffff0000) | (0);    /* lcd */
    }

    enhance_data_lock = hal_spin_lock_irqsave(&disp_lock);
    enhancep->config.info.enable = 1;
    enhancep->config.flags |= ENH_ENABLE_DIRTY | ENH_SIZE_DIRTY;

    if ((enhancep->config.info.window.width == 0)
        || (enhancep->config.info.window.height == 0)) {
        enhancep->config.info.window.width =
            enhancep->config.info.size.width;
        enhancep->config.info.window.height =
            enhancep->config.info.size.height;
    }

    enhancep->enabled = 1;
    hal_spin_unlock_irqrestore(&disp_lock, enhance_data_lock);

    disp_enhance_apply(enhance);
    return 0;
}

static s32 disp_enhance_disable(struct disp_enhance *enhance)
{
    struct disp_enhance_private_data *enhancep =
        disp_enhance_get_priv(enhance);

    if ((enhance == NULL) || (enhancep == NULL)) {
        DE_INF("NULL hdl!\n");
        return -1;
    }

    enhance_data_lock = hal_spin_lock_irqsave(&disp_lock);
    enhancep->config.info.enable = 0;
    enhancep->config.flags |= ENH_ENABLE_DIRTY;

    enhancep->enabled = 0;
    hal_spin_unlock_irqrestore(&disp_lock, enhance_data_lock);

    disp_enhance_apply(enhance);

    return 0;
}

static s32 disp_enhance_demo_enable(struct disp_enhance *enhance)
{
    struct disp_enhance_private_data *enhancep = disp_enhance_get_priv(enhance);

    if ((NULL == enhance) || (NULL == enhancep)) {
        DE_INF("NULL hdl!\n");
        return -1;
    }

    enhance_data_lock = hal_spin_lock_irqsave(&disp_lock);
    enhancep->config.info.demo_enable = 1;
    hal_spin_unlock_irqrestore(&disp_lock, enhance_data_lock);

    disp_enhance_apply(enhance);
    return 0;
}

static s32 disp_enhance_demo_disable(struct disp_enhance *enhance)
{
    struct disp_enhance_private_data *enhancep = disp_enhance_get_priv(enhance);

    if ((NULL == enhance) || (NULL == enhancep)) {
        DE_INF("NULL hdl!\n");
        return -1;
    }

    enhance_data_lock = hal_spin_lock_irqsave(&disp_lock);
    enhancep->config.info.demo_enable = 0;
    hal_spin_unlock_irqrestore(&disp_lock, enhance_data_lock);

    disp_enhance_apply(enhance);
    return 0;
}

static s32 disp_enhance_set_mode(struct disp_enhance *enhance, u32 mode)
{
    struct disp_enhance_private_data *enhancep = disp_enhance_get_priv(enhance);

    if ((NULL == enhance) || (NULL == enhancep)) {
        DE_INF("NULL hdl!\n");
        return -1;
    }

    enhance_data_lock = hal_spin_lock_irqsave(&disp_lock);
    enhancep->config.info.mode = (enhancep->config.info.mode & 0xffff)  | (mode << 16);
    enhancep->config.flags |= ENH_MODE_DIRTY;
    hal_spin_unlock_irqrestore(&disp_lock, enhance_data_lock);

    disp_enhance_apply(enhance);
    return 0;
}

static s32 disp_enhance_get_mode(struct disp_enhance *enhance)
{
    struct disp_enhance_private_data *enhancep = disp_enhance_get_priv(enhance);

    if ((NULL == enhance) || (NULL == enhancep)) {
        DE_INF("NULL hdl!\n");
        return 0;
    }

    return enhancep->config.info.mode >> 16;
}

static s32 disp_enhance_set_bright(struct disp_enhance *enhance, u32 value)
{
    struct disp_enhance_private_data *enhancep =
        disp_enhance_get_priv(enhance);

    if ((enhance == NULL) || (enhancep == NULL)) {
        DE_INF("NULL hdl!\n");
        return -1;
    }

    enhance_data_lock = hal_spin_lock_irqsave(&disp_lock);
    enhancep->config.info.bright = value;
    enhancep->config.flags |= ENH_BRIGHT_DIRTY;
    hal_spin_unlock_irqrestore(&disp_lock, enhance_data_lock);

    disp_enhance_apply(enhance);

    return 0;
}

static s32 disp_enhance_get_bright(struct disp_enhance *enhance)
{
    struct disp_enhance_private_data *enhancep =
        disp_enhance_get_priv(enhance);

    if ((NULL == enhance) || (NULL == enhancep)) {
        DE_INF("NULL hdl!\n");
        return 0;
    }

    return enhancep->config.info.bright;
}

static s32 disp_enhance_set_saturation(struct disp_enhance *enhance, u32 value)
{
    struct disp_enhance_private_data *enhancep =
        disp_enhance_get_priv(enhance);

    if ((NULL == enhance) || (NULL == enhancep)) {
        DE_INF("NULL hdl!\n");
        return -1;
    }

    enhance_data_lock = hal_spin_lock_irqsave(&disp_lock);
    enhancep->config.info.saturation = value;
    enhancep->config.flags |= ENH_SAT_DIRTY;
    hal_spin_unlock_irqrestore(&disp_lock, enhance_data_lock);

    disp_enhance_apply(enhance);
    return 0;
}

static s32 disp_enhance_get_saturation(struct disp_enhance *enhance)
{
    struct disp_enhance_private_data *enhancep =
        disp_enhance_get_priv(enhance);

    if ((NULL == enhance) || (NULL == enhancep)) {
        DE_INF("NULL hdl!\n");
        return 0;
    }

    return enhancep->config.info.saturation;
}

static s32 disp_enhance_set_contrast(struct disp_enhance *enhance, u32 value)
{
    struct disp_enhance_private_data *enhancep =
        disp_enhance_get_priv(enhance);

    if ((NULL == enhance) || (NULL == enhancep)) {
        DE_INF("NULL hdl!\n");
        return -1;
    }

    enhance_data_lock = hal_spin_lock_irqsave(&disp_lock);
    enhancep->config.info.contrast = value;
    enhancep->config.flags |= ENH_CONTRAST_DIRTY;
    hal_spin_unlock_irqrestore(&disp_lock, enhance_data_lock);

    disp_enhance_apply(enhance);

    return 0;
}

static s32 disp_enhance_get_contrast(struct disp_enhance *enhance)
{
    struct disp_enhance_private_data *enhancep =
        disp_enhance_get_priv(enhance);

    if ((NULL == enhance) || (NULL == enhancep)) {
        DE_INF("NULL hdl!\n");
        return 0;
    }

    return enhancep->config.info.contrast;
}

static s32 disp_enhance_set_edge(struct disp_enhance *enhance, u32 value)
{
    struct disp_enhance_private_data *enhancep =
        disp_enhance_get_priv(enhance);

    if ((enhance == NULL) || (enhancep == NULL)) {
        DE_INF("NULL hdl!\n");
        return -1;
    }

    enhance_data_lock = hal_spin_lock_irqsave(&disp_lock);
    enhancep->config.info.edge = value;
    enhancep->config.flags |= ENH_EDGE_DIRTY;
    hal_spin_unlock_irqrestore(&disp_lock, enhance_data_lock);

    disp_enhance_apply(enhance);

    return 0;
}

static s32 disp_enhance_get_edge(struct disp_enhance *enhance)
{
    struct disp_enhance_private_data *enhancep =
        disp_enhance_get_priv(enhance);

    if ((NULL == enhance) || (NULL == enhancep)) {
        DE_INF("NULL hdl!\n");
        return 0;
    }

    return enhancep->config.info.edge;
}

static s32 disp_enhance_set_detail(struct disp_enhance *enhance, u32 value)
{
    struct disp_enhance_private_data *enhancep =
        disp_enhance_get_priv(enhance);

    if ((NULL == enhance) || (NULL == enhancep)) {
        DE_INF("NULL hdl!\n");
        return -1;
    }

    enhance_data_lock = hal_spin_lock_irqsave(&disp_lock);
    enhancep->config.info.detail = value;
    enhancep->config.flags |= ENH_DETAIL_DIRTY;
    hal_spin_unlock_irqrestore(&disp_lock, enhance_data_lock);

    disp_enhance_apply(enhance);

    return 0;
}

static s32 disp_enhance_get_detail(struct disp_enhance *enhance)
{
    struct disp_enhance_private_data *enhancep =
        disp_enhance_get_priv(enhance);

    if ((enhance == NULL) || (enhancep == NULL)) {
        DE_INF("NULL hdl!\n");
        return 0;
    }

    return enhancep->config.info.detail;
}

static s32 disp_enhance_set_denoise(struct disp_enhance *enhance, u32 value)
{
    struct disp_enhance_private_data *enhancep =
        disp_enhance_get_priv(enhance);

    if ((NULL == enhance) || (NULL == enhancep)) {
        DE_INF("NULL hdl!\n");
        return -1;
    }

    enhance_data_lock = hal_spin_lock_irqsave(&disp_lock);
    enhancep->config.info.denoise = value;
    enhancep->config.flags |= ENH_DNS_DIRTY;
    hal_spin_unlock_irqrestore(&disp_lock, enhance_data_lock);

    disp_enhance_apply(enhance);

    return 0;
}

static s32 disp_enhance_get_denoise(struct disp_enhance *enhance)
{
    struct disp_enhance_private_data *enhancep =
        disp_enhance_get_priv(enhance);

    if ((NULL == enhance) || (NULL == enhancep)) {
        DE_INF("NULL hdl!\n");
        return 0;
    }

    return enhancep->config.info.denoise;
}

static s32 disp_enhance_set_manager(struct disp_enhance *enhance,
                    struct disp_manager *mgr)
{

    if ((enhance == NULL) || (mgr == NULL)) {
        DE_INF("NULL hdl!\n");
        return -1;
    }

    enhance_data_lock = hal_spin_lock_irqsave(&disp_lock);
    enhance->manager = mgr;
    mgr->enhance = enhance;
    hal_spin_unlock_irqrestore(&disp_lock, enhance_data_lock);

    return 0;
}

static s32 disp_enhance_unset_manager(struct disp_enhance *enhance)
{

    if (enhance == NULL) {
        DE_INF("NULL hdl!\n");
        return -1;
    }

    enhance_data_lock = hal_spin_lock_irqsave(&disp_lock);
    if (enhance->manager)
        enhance->manager->enhance = NULL;
    enhance->manager = NULL;
    hal_spin_unlock_irqrestore(&disp_lock, enhance_data_lock);

    return 0;
}

static s32 disp_enhance_shadow_protect(struct disp_enhance *enhance,
                       bool protect)
{
    struct disp_enhance_private_data *enhancep =
        disp_enhance_get_priv(enhance);

    if ((enhance == NULL) || (enhancep == NULL)) {
        DE_INF("NULL hdl!\n");
        return -1;
    }

    if (enhancep->shadow_protect)
        return enhancep->shadow_protect(enhance->disp, protect);

    return -1;
}

static s32 disp_enhance_dump(struct disp_enhance *enhance, char *buf)
{
    struct disp_enhance_config config;
    struct disp_enhance_private_data *enhancep =
        disp_enhance_get_priv(enhance);
    u32 count = 0;

    if ((enhance == NULL) || (enhancep == NULL)) {
        DE_INF("NULL hdl!\n");
        return -1;
    }

    memcpy(&config, &enhancep->config, sizeof(struct disp_enhance_config));

    count += sprintf(buf + count, "enhance %d: %s, %s\n",
             enhance->disp,
             (config.info.enable == 1) ? "enable" : "disable",
             (config.info.demo_enable == 1) ? "demo" : "normal");

    return count;
}

static s32 disp_enhance_init(struct disp_enhance *enhance)
{
    struct disp_enhance_private_data *enhancep =
        disp_enhance_get_priv(enhance);

    if ((enhance == NULL) || (enhancep == NULL)) {
        DE_INF("NULL hdl!\n");
        return -1;
    }

    return 0;
}

static s32 disp_enhance_exit(struct disp_enhance *enhance)
{
    struct disp_enhance_private_data *enhancep =
        disp_enhance_get_priv(enhance);

    if ((enhance == NULL) || (enhancep == NULL)) {
        DE_INF("NULL hdl!\n");
        return -1;
    }

    return 0;
}

/* for inner debug */
s32 disp_enhance_set_para(struct disp_enhance *enhance,
              struct disp_enhance_para *para)
{
    unsigned long flags;
    struct disp_enhance_private_data *enhancep =
        disp_enhance_get_priv(enhance);
    struct disp_device *dispdev = NULL;

    if ((enhance == NULL) || (enhancep == NULL)) {
        DE_INF("NULL hdl!\n");
        return -1;
    }
    if (enhance->manager)
        dispdev = enhance->manager->device;
    if (dispdev)
        dispdev->get_resolution(dispdev,
                    &enhancep->config.info.size.width,
                    &enhancep->config.info.size.height);

    enhance_data_lock = hal_spin_lock_irqsave(&disp_lock);
    memcpy(&enhancep->config.info.window, &para->window,
           sizeof(struct disp_rect));
    enhancep->config.info.enable = para->enable;
    enhancep->config.flags |= ENH_ENABLE_DIRTY | ENH_SIZE_DIRTY;

    if ((enhancep->config.info.window.width == 0)
        || (enhancep->config.info.window.height == 0)) {
        enhancep->config.info.window.width =
            enhancep->config.info.size.width;
        enhancep->config.info.window.height =
            enhancep->config.info.size.height;
    }

    enhancep->config.info.bright = para->bright;
    enhancep->config.info.contrast = para->contrast;
    enhancep->config.info.saturation = para->saturation;
    enhancep->config.info.hue = para->hue;
    enhancep->config.info.sharp = para->sharp;
    enhancep->config.info.auto_contrast = para->auto_contrast;

    enhancep->config.info.auto_color = para->auto_color;
    enhancep->config.info.fancycolor_red = para->fancycolor_red;
    enhancep->config.info.fancycolor_blue = para->fancycolor_blue;
    enhancep->config.info.fancycolor_green = para->fancycolor_green;

    enhancep->enabled = para->enable;
    hal_spin_unlock_irqrestore(&disp_lock, enhance_data_lock);
    DE_INF
        ("en=%d,para=%d,%d,%d,%d,sharp=%d,auto=%d,%d,fancycolor=%d,%d,%d\n",
         enhancep->config.info.enable, enhancep->config.info.bright,
         enhancep->config.info.contrast, enhancep->config.info.saturation,
         enhancep->config.info.hue, enhancep->config.info.sharp,
         enhancep->config.info.auto_color,
         enhancep->config.info.auto_contrast,
         enhancep->config.info.fancycolor_red,
         enhancep->config.info.fancycolor_green,
         enhancep->config.info.fancycolor_blue);

    disp_enhance_apply(enhance);
    return 0;
}

s32 disp_init_enhance(struct disp_bsp_init_para *para)
{
    u32 num_enhances;
    u32 disp;
    struct disp_enhance *enhance;
    struct disp_enhance_private_data *enhancep;

    DE_INF("disp_init_enhance\n");
    num_enhances = bsp_disp_feat_get_num_screens();
    enhances =
        disp_sys_malloc(num_enhances * sizeof(struct disp_enhance));
    if (enhances == NULL) {
        DE_WRN("malloc memory fail!\n");
        goto malloc_err;
    }
    enhance_private =
        (struct disp_enhance_private_data *)
        disp_sys_malloc(sizeof(struct disp_enhance_private_data)
            * num_enhances);
    if (enhance_private == NULL) {
        DE_WRN("malloc memory fail!\n");
        goto malloc_err;
    }

    for (disp = 0; disp < num_enhances; disp++) {
        if (bsp_disp_feat_is_support_enhance(disp) == 0)
            continue;

        enhance = &enhances[disp];
        enhancep = &enhance_private[disp];

        switch (disp) {
        case 0:
            enhance->name = "enhance0";
            enhance->disp = 0;
            break;
        case 1:
            enhance->name = "enhance1";
            enhance->disp = 1;
            break;
        case 2:
            enhance->name = "enhance2";
            enhance->disp = 2;

            break;
        }
        enhancep->shadow_protect = para->shadow_protect;

        enhance->enable = disp_enhance_enable;
        enhance->disable = disp_enhance_disable;
        enhance->is_enabled = disp_enhance_is_enabled;
        enhance->init = disp_enhance_init;
        enhance->exit = disp_enhance_exit;
        enhance->apply = disp_enhance_apply;
        enhance->update_regs = disp_enhance_update_regs;
        enhance->force_apply = disp_enhance_force_apply;
        enhance->sync = disp_enhance_sync;
        enhance->tasklet = disp_enhance_tasklet;
        enhance->set_manager = disp_enhance_set_manager;
        enhance->unset_manager = disp_enhance_unset_manager;
        enhance->set_para = disp_enhance_set_para;
        enhance->dump = disp_enhance_dump;
        enhance->demo_enable = disp_enhance_demo_enable;
        enhance->demo_disable = disp_enhance_demo_disable;
        enhance->set_mode = disp_enhance_set_mode;
        enhance->get_mode = disp_enhance_get_mode;
        enhance->set_bright = disp_enhance_set_bright;
        enhance->get_bright = disp_enhance_get_bright;
        enhance->set_saturation = disp_enhance_set_saturation;
        enhance->get_saturation = disp_enhance_get_saturation;
        enhance->set_contrast = disp_enhance_set_contrast;
        enhance->get_contrast = disp_enhance_get_contrast;
        enhance->set_edge = disp_enhance_set_edge;
        enhance->get_edge = disp_enhance_get_edge;
        enhance->set_detail = disp_enhance_set_detail;
        enhance->get_detail = disp_enhance_get_detail;
        enhance->set_denoise = disp_enhance_set_denoise;
        enhance->get_denoise = disp_enhance_get_denoise;

        enhance->init(enhance);
    }

    return 0;
malloc_err:
    disp_sys_free(enhance_private);
    disp_sys_free(enhances);
    enhance_private = NULL;
    enhances = NULL;

    return -1;
}

s32 disp_exit_enhance(void)
{
    u32 num_enhances;
    u32 disp;
    struct disp_enhance *enhance;

    if (!enhances)
        return 0;

    num_enhances = bsp_disp_feat_get_num_screens();
    for (disp = 0; disp < num_enhances; disp++) {
        if (bsp_disp_feat_is_support_enhance(disp) == 0)
            continue;

        enhance = &enhances[disp];
        enhance->exit(enhance);
    }

    disp_sys_free(enhance_private);
    disp_sys_free(enhances);

    return 0;
}

#endif
