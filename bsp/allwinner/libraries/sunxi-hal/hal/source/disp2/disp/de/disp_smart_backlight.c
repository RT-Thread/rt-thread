/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#include "disp_smart_backlight.h"
#include <hal_atomic.h>

struct disp_smbl_private_data {
    struct disp_smbl_info info;
    bool applied;

     s32 (*shadow_protect)(u32 sel, bool protect);

    u32 enabled;
    hal_sem_t mlock;
};
static u32 smbl_data_lock;

/* #define SMBL_NO_AL */
static struct disp_smbl *smbls;
static struct disp_smbl_private_data *smbl_private;

struct disp_smbl *disp_get_smbl(u32 disp)
{
    u32 num_screens;

    num_screens = bsp_disp_feat_get_num_screens();
    if (disp >= num_screens) {
        DE_WRN("disp %d out of range\n", disp);
        return NULL;
    }
    DE_INF("get smbl%d ok\n", disp);

    if (bsp_disp_feat_is_support_smbl(disp))
        return &smbls[disp];
    else
        return NULL;
}
static struct disp_smbl_private_data *disp_smbl_get_priv(struct disp_smbl *smbl)
{
    if (smbl == NULL) {
        DE_INF("NULL hdl!\n");
        return NULL;
    }

    return &smbl_private[smbl->disp];
}

static s32 disp_smbl_update_regs(struct disp_smbl *smbl)
{
    struct disp_smbl_private_data *smblp = disp_smbl_get_priv(smbl);
    bool applied = false;

    if ((smbl == NULL) || (smblp == NULL)) {
        DE_INF("NULL hdl!\n");
        return -1;
    }
    smbl_data_lock = hal_spin_lock_irqsave(&disp_lock);
    if (true == smblp->applied) {
        applied = true;
        smblp->applied = false;
    }
    hal_spin_unlock_irqrestore(&disp_lock, smbl_data_lock);

    disp_al_smbl_update_regs(smbl->disp);

    return 0;
}

/* should protect width @mlock */
static s32 disp_smbl_update_backlight(struct disp_smbl *smbl, unsigned int bl)
{
    if (smbl == NULL) {
        DE_INF("NULL hdl!\n");
        return -1;
    }

    smbl->backlight = bl;
    smbl->apply(smbl);

    return 0;
}

/* should protect width @mlock */
static s32 disp_smbl_apply(struct disp_smbl *smbl)
{
    struct disp_smbl_private_data *smblp = disp_smbl_get_priv(smbl);
    struct disp_smbl_info info;

    if ((smbl == NULL) || (smblp == NULL)) {
        DE_INF("NULL hdl!\n");
        return -1;
    }

    memset(&info, 0, sizeof(struct disp_smbl_info));

    /* disp_sys_mutex_lock(&smblp->mlock); */
    if (smbl->backlight != smblp->info.backlight) {
        smblp->info.backlight = smbl->backlight;
        smblp->info.flags |= SMBL_DIRTY_BL;
    }
    if (smblp->info.flags != SMBL_DIRTY_NONE) {
        memcpy(&info, &smblp->info, sizeof(struct disp_smbl_info));
        smblp->info.flags = SMBL_DIRTY_NONE;
        disp_smbl_shadow_protect(smbl, true);
        disp_al_smbl_apply(smbl->disp, &info);
        disp_smbl_shadow_protect(smbl, false);
        smbl_data_lock = hal_spin_lock_irqsave(&disp_lock);
        smblp->applied = true;
        hal_spin_unlock_irqrestore(&disp_lock, smbl_data_lock);
    }
    /* disp_sys_mutex_unlock(&smblp->mlock); */

    return 0;
}

static s32 disp_smbl_force_apply(struct disp_smbl *smbl)
{
    struct disp_smbl_private_data *smblp = disp_smbl_get_priv(smbl);

    if ((smbl == NULL) || (smblp == NULL)) {
        DE_INF("NULL hdl!\n");
        return -1;
    }

    disp_sys_mutex_lock(&smblp->mlock);
    smblp->info.flags = SMBL_DIRTY_ALL;
    disp_smbl_apply(smbl);
    disp_smbl_update_regs(smbl);
    disp_sys_mutex_unlock(&smblp->mlock);

    return 0;
}

static s32 disp_smbl_sync(struct disp_smbl *smbl)
{
    if (smbl == NULL) {
        DE_INF("NULL hdl!\n");
        return -1;
    }

    disp_smbl_update_regs(smbl);

    return 0;
}

static s32 disp_smbl_tasklet(struct disp_smbl *smbl)
{
    struct disp_smbl_private_data *smblp = disp_smbl_get_priv(smbl);
    struct disp_manager *mgr;
    unsigned int dimming;
    bool dimming_update = false;

    if ((smbl == NULL) || (smblp == NULL)) {
        DE_INF("NULL hdl!\n");
        return -1;
    }

    disp_al_smbl_tasklet(smbl->disp);
    dimming = disp_al_smbl_get_status(smbl->disp);
    if (smblp->info.backlight_dimming != dimming) {
        smblp->info.backlight_dimming = dimming;
        dimming_update = true;
    }

    mgr = smbl->manager;
    if (mgr && mgr->device) {
        struct disp_device *dispdev = mgr->device;

        if (dispdev->set_bright_dimming && dimming_update) {
            if (dispdev->set_bright_dimming)
                dispdev->set_bright_dimming(dispdev,
                        smblp->info.backlight_dimming);
        }
    }

    return 0;
}

static bool disp_smbl_is_enabled(struct disp_smbl *smbl)
{
    struct disp_smbl_private_data *smblp = disp_smbl_get_priv(smbl);

    if ((smbl == NULL) || (smblp == NULL)) {
        DE_INF("NULL hdl!\n");
        return false;
    }

    return (smblp->info.enable == 1);
}

static s32 disp_smbl_enable(struct disp_smbl *smbl)
{
    struct disp_smbl_private_data *smblp = disp_smbl_get_priv(smbl);
    struct disp_device *dispdev = NULL;

    if ((smbl == NULL) || (smblp == NULL)) {
        DE_INF("NULL hdl!\n");
        return -1;
    }
    if (smbl->manager)
        dispdev = smbl->manager->device;
    if (dispdev)
        dispdev->get_resolution(dispdev, &smblp->info.size.width,
                    &smblp->info.size.height);

    if ((smblp->info.window.width == 0)
        || (smblp->info.window.height == 0)) {
        smblp->info.window.width = smblp->info.size.width;
        smblp->info.window.height = smblp->info.size.height;
    }

    DE_INF("smbl %d enable\n", smbl->disp);
    disp_sys_mutex_lock(&smblp->mlock);
    smblp->info.enable = 1;
    smblp->info.flags |= SMBL_DIRTY_ENABLE;
    disp_smbl_apply(smbl);
    disp_sys_mutex_unlock(&smblp->mlock);

    return 0;
}

static s32 disp_smbl_disable(struct disp_smbl *smbl)
{
    struct disp_smbl_private_data *smblp = disp_smbl_get_priv(smbl);

    if ((smbl == NULL) || (smblp == NULL)) {
        DE_INF("NULL hdl!\n");
        return -1;
    }
    DE_INF("smbl %d disable\n", smbl->disp);

    disp_sys_mutex_lock(&smblp->mlock);
    smblp->info.enable = 0;
    smblp->info.flags |= SMBL_DIRTY_ENABLE;
    disp_smbl_apply(smbl);
    disp_sys_mutex_unlock(&smblp->mlock);

    return 0;
}

s32 disp_smbl_shadow_protect(struct disp_smbl *smbl, bool protect)
{
    struct disp_smbl_private_data *smblp = disp_smbl_get_priv(smbl);

    if ((smbl == NULL) || (smblp == NULL)) {
        DE_INF("NULL hdl!\n");
        return -1;
    }

    if (smblp->shadow_protect)
        return smblp->shadow_protect(smbl->disp, protect);

    return -1;
}

static s32 disp_smbl_set_window(struct disp_smbl *smbl,
                struct disp_rect *window)
{
    struct disp_smbl_private_data *smblp = disp_smbl_get_priv(smbl);

    if ((smbl == NULL) || (smblp == NULL)) {
        DE_INF("NULL hdl!\n");
        return -1;
    }
    disp_sys_mutex_lock(&smblp->mlock);
    memcpy(&smblp->info.window, window, sizeof(struct disp_rect));
    smblp->info.flags |= SMBL_DIRTY_WINDOW;
    disp_smbl_apply(smbl);
    disp_sys_mutex_unlock(&smblp->mlock);

    return 0;
}

static s32 disp_smbl_get_window(struct disp_smbl *smbl,
                struct disp_rect *window)
{
    struct disp_smbl_private_data *smblp = disp_smbl_get_priv(smbl);

    if ((smbl == NULL) || (smblp == NULL)) {
        DE_INF("NULL hdl!\n");
        return -1;
    }
    disp_sys_mutex_lock(&smblp->mlock);
    memcpy(window, &smblp->info.window, sizeof(struct disp_rect));
    disp_sys_mutex_unlock(&smblp->mlock);

    return 0;
}

static s32 disp_smbl_set_manager(struct disp_smbl *smbl,
                 struct disp_manager *mgr)
{
    struct disp_smbl_private_data *smblp = disp_smbl_get_priv(smbl);

    if ((smbl == NULL) || (mgr == NULL) || (smblp == NULL)) {
        DE_INF("NULL hdl!\n");
        return -1;
    }

    DE_INF("smbl %d -> mgr %d\n", smbl->disp, mgr->disp);
    disp_sys_mutex_lock(&smblp->mlock);
    smbl->manager = mgr;
    mgr->smbl = smbl;
    disp_sys_mutex_unlock(&smblp->mlock);

    return 0;
}

static s32 disp_smbl_unset_manager(struct disp_smbl *smbl)
{
    struct disp_smbl_private_data *smblp = disp_smbl_get_priv(smbl);

    if ((smbl == NULL) || (smblp == NULL)) {
        DE_INF("NULL hdl!\n");
        return -1;
    }
    disp_sys_mutex_lock(&smblp->mlock);
    if (smbl->manager)
        smbl->manager->smbl = NULL;
    smbl->manager = NULL;
    disp_sys_mutex_unlock(&smblp->mlock);

    return 0;
}

static s32 disp_smbl_dump(struct disp_smbl *smbl, char *buf)
{
    struct disp_smbl_info info;
    struct disp_smbl_private_data *smblp = disp_smbl_get_priv(smbl);
    u32 count = 0;

    if ((smbl == NULL) || (smblp == NULL)) {
        DE_INF("NULL hdl!\n");
        return -1;
    }

    memcpy(&info, &smblp->info, sizeof(struct disp_smbl_info));

    count +=
        sprintf(buf + count,
            "smart_backlight %d: %s, window<%d,%d,%d,%d>, backlight=%d, save_power=%d percent\n",
            smbl->disp, (info.enable == 1) ? "enable" : "disable",
            info.window.x, info.window.y, info.window.width,
            info.window.height, smbl->backlight,
            100 - info.backlight_dimming * 100 / 256);

    return count;
}

static s32 disp_smbl_init(struct disp_smbl *smbl)
{
    struct disp_smbl_private_data *smblp = disp_smbl_get_priv(smbl);

    if ((smbl == NULL) || (smblp == NULL)) {
        DE_INF("NULL hdl!\n");
        return -1;
    }

    return 0;
}

static s32 disp_smbl_exit(struct disp_smbl *smbl)
{
    struct disp_smbl_private_data *smblp = disp_smbl_get_priv(smbl);

    if ((smbl == NULL) || (smblp == NULL)) {
        DE_INF("NULL hdl!\n");
        return -1;
    }

    return 0;
}

s32 disp_init_smbl(struct disp_bsp_init_para *para)
{
    u32 num_smbls;
    u32 disp;
    struct disp_smbl *smbl;
    struct disp_smbl_private_data *smblp;

    DE_INF("disp_init_smbl\n");

    smbl_data_lock = 0;
    num_smbls = bsp_disp_feat_get_num_screens();
    smbls =
        disp_sys_malloc(num_smbls * sizeof(struct disp_smbl));
    if (smbls == NULL) {
        DE_WRN("malloc memory fail!\n");
        goto malloc_err;
    }
    smbl_private =
        (struct disp_smbl_private_data *)
        disp_sys_malloc(sizeof(struct disp_smbl_private_data)
            * num_smbls);
    if (smbl_private == NULL) {
        DE_WRN("malloc memory fail!\n");
        goto malloc_err;
    }

    for (disp = 0; disp < num_smbls; disp++) {
        if (!bsp_disp_feat_is_support_smbl(disp))
            continue;

        smbl = &smbls[disp];
        smblp = &smbl_private[disp];
        disp_sys_mutex_init(&smblp->mlock);

        switch (disp) {
        case 0:
            smbl->name = "smbl0";
            smbl->disp = 0;

            break;
        case 1:
            smbl->name = "smbl1";
            smbl->disp = 1;

            break;
        case 2:
            smbl->name = "smbl2";
            smbl->disp = 2;

            break;
        }
        smblp->shadow_protect = para->shadow_protect;

        smbl->enable = disp_smbl_enable;
        smbl->disable = disp_smbl_disable;
        smbl->is_enabled = disp_smbl_is_enabled;
        smbl->init = disp_smbl_init;
        smbl->exit = disp_smbl_exit;
        smbl->apply = disp_smbl_apply;
        smbl->force_apply = disp_smbl_force_apply;
        smbl->update_regs = disp_smbl_update_regs;
        smbl->sync = disp_smbl_sync;
        smbl->tasklet = disp_smbl_tasklet;
        smbl->set_manager = disp_smbl_set_manager;
        smbl->unset_manager = disp_smbl_unset_manager;
        smbl->set_window = disp_smbl_set_window;
        smbl->get_window = disp_smbl_get_window;
        smbl->update_backlight = disp_smbl_update_backlight;
        smbl->dump = disp_smbl_dump;

        smbl->init(smbl);
    }

    return 0;

malloc_err:
    disp_sys_free(smbl_private);
    disp_sys_free(smbls);
    smbl_private = NULL;
    smbls = NULL;

    return -1;
}

s32 disp_exit_smbl(void)
{
    u32 num_smbls;
    u32 disp;
    struct disp_smbl *smbl;

    if (!smbls)
        return 0;

    num_smbls = bsp_disp_feat_get_num_screens();
    for (disp = 0; disp < num_smbls; disp++) {
        if (!bsp_disp_feat_is_support_smbl(disp))
            continue;

        smbl = &smbls[disp];
        smbl->exit(smbl);
    }

    disp_sys_free(smbl_private);
    disp_sys_free(smbls);
    smbl_private = NULL;
    smbls = NULL;

    return 0;
}

