/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2024-07-04     rcitach        init ver.
 */

#include <rtthread.h>
#include <mmu.h>
#include <gtimer.h>
#include <lwp_user_mm.h>

#include "vdso.h"
#include "vdso_datapage.h"
#define DBG_TAG    "vdso"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

enum vdso_abi {
    VDSO_ABI_AA64,
};
enum vvar_pages {
    VVAR_DATA_PAGE_OFFSET,
    VVAR_TIMENS_PAGE_OFFSET,
    VVAR_NR_PAGES,
};
struct vdso_abi_info {
    const char *name;
    const char *vdso_code_start;
    const char *vdso_code_end;
    unsigned long vdso_pages;

};

static struct vdso_abi_info vdso_info[] = {
    [VDSO_ABI_AA64] = {
        .name = "vdso_aarch64",
        .vdso_code_start = __vdso_text_start,
        .vdso_code_end = __vdso_text_end,
    },
};

static union {
    struct vdso_data    data[CS_BASES];
    uint8_t         page[ARCH_PAGE_SIZE];
} vdso_data_store __page_aligned_data;
struct vdso_data *vdso_data = vdso_data_store.data;
int init_ret_flag = RT_EOK;

static int __setup_additional_pages(enum vdso_abi abi, struct rt_lwp *lwp)
{
    RT_ASSERT(lwp != RT_NULL);

    int ret;
    void *vdso_base = RT_NULL;
    unsigned long vdso_data_len, vdso_text_len;

    vdso_data_len = VVAR_NR_PAGES * ARCH_PAGE_SIZE;
    vdso_text_len = vdso_info[abi].vdso_pages << ARCH_PAGE_SHIFT;

    vdso_base = lwp_map_user_phy(lwp, RT_NULL, rt_kmem_v2p((void *)vdso_data), vdso_data_len, 0);
    if(vdso_base != RT_NULL)
    {
        ret = RT_EOK;
    }
    else
    {
        ret = RT_ERROR;
    }
    vdso_base += vdso_data_len;
    vdso_base = lwp_map_user_phy(lwp, vdso_base, rt_kmem_v2p((void *)vdso_info[abi].vdso_code_start), vdso_text_len, 0);

    lwp->vdso_vbase = vdso_base;
    return ret;
}

int arch_setup_additional_pages(struct rt_lwp *lwp)
{
    int ret;
    if (init_ret_flag != RT_EOK) return -RT_ERROR;
    ret = __setup_additional_pages(VDSO_ABI_AA64, lwp);

    return ret;
}

static void __initdata(void)
{
    struct tm time_vdso = SOFT_RTC_VDSOTIME_DEFAULT;
    vdso_data->realtime_initdata = timegm(&time_vdso);
}

static int validate_vdso_elf(void)
{
    if (rt_memcmp(vdso_info[VDSO_ABI_AA64].vdso_code_start, ELF_HEAD, ELF_HEAD_LEN)) {
        LOG_E("vDSO is not a valid ELF object!");
        init_ret_flag = -RT_ERROR;
        return -RT_ERROR;
    }
    vdso_info[VDSO_ABI_AA64].vdso_pages = (
        vdso_info[VDSO_ABI_AA64].vdso_code_end -
        vdso_info[VDSO_ABI_AA64].vdso_code_start) >>
        ARCH_PAGE_SHIFT;

    __initdata();
    return RT_EOK;
}
INIT_COMPONENT_EXPORT(validate_vdso_elf);
