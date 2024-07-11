/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2024-07-04     rcitach        init ver.
 */

#ifndef _VDSO_KDATA_H
#define _VDSO_KDATA_H

#include <rtatomic.h>
#include <vdso_datapage.h>

#ifdef __cplusplus
extern "C" {
#endif

extern struct vdso_data *vdso_data;

rt_inline
struct vdso_data *_get_k_vdso_data(void)
{
    return vdso_data;
}
#define get_k_vdso_data _get_k_vdso_data

rt_inline
void rt_vdso_write_begin(struct vdso_data *vd)
{
    rt_atomic_add(&vd[CS_HRES_COARSE].seq, 1);
    rt_atomic_add(&vd[CS_RAW].seq, 1);
}

rt_inline
void rt_vdso_write_end(struct vdso_data *vd)
{
    rt_atomic_add(&vd[CS_HRES_COARSE].seq, 1);
    rt_atomic_add(&vd[CS_RAW].seq, 1);
}

#ifdef __cplusplus
}
#endif

#endif /* _VDSO_KDATA_H */
