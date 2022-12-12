/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */


#ifndef __DISP_CAPTURE_H__
#define __DISP_CAPTURE_H__

#include "disp_private.h"

s32 disp_capture_start(struct disp_capture *cptr);
s32 disp_capture_stop(struct disp_capture *cptr);
s32 disp_capture_commit(struct disp_capture *cptr,
            struct disp_capture_info *info);
s32 disp_capture_set_manager(struct disp_capture *cptr,
                 struct disp_manager *mgr);
s32 disp_capture_unset_manager(struct disp_capture *cptr);
s32 disp_capture_init(struct disp_capture *cptr);
s32 disp_capture_exit(struct disp_capture *cptr);
s32 disp_capture_sync(struct disp_capture *cptr);
s32 disp_init_capture(struct disp_bsp_init_para *para);
s32 disp_capture_shadow_protect(struct disp_capture *capture, bool protect);
s32 disp_capture_apply(struct disp_capture *cptr);
s32 disp_capture_force_apply(struct disp_capture *cptr);
s32 disp_capture_suspend(struct disp_capture *cptr);
s32 disp_capture_resume(struct disp_capture *cptr);
s32 disp_capture_query(struct disp_capture *cptr);

#endif
