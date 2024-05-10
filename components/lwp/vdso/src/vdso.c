#include <rtthread.h>
#include <mmu.h>
#include <lwp_user_mm.h>

#include "vdso.h"
#include "vdso_datapage.h"
#define DBG_TAG    "vdso"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

enum vdso_abi {
	VDSO_ABI_AA64,
	VDSO_ABI_AA32,
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

time_t init_vdso_time;

/* 2018-01-30 14:44:50 = RTC_TIME_INIT(2018, 1, 30, 14, 44, 50)  */
#define RTC_TIME_INIT(year, month, day, hour, minute, second)        \
    {.tm_year = year - 1900, .tm_mon = month - 1, .tm_mday = day, .tm_hour = hour, .tm_min = minute, .tm_sec = second}

#ifndef SOFT_RTC_TIME_DEFAULT
#define SOFT_RTC_TIME_DEFAULT                    RTC_TIME_INIT(2018, 1, 1, 0, 0 ,0)
#endif

static union {
	VdsoDataPage	data[CS_BASES];
	uint8_t			page[ARCH_PAGE_SIZE];
} vdso_data_store __page_aligned_data;
VdsoDataPage *vdso_data = vdso_data_store.data;

int __setup_additional_pages(enum vdso_abi abi, struct rt_lwp *lwp)
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
	vdso_base += VVAR_NR_PAGES * ARCH_PAGE_SIZE;
	vdso_base = lwp_map_user_phy(lwp, vdso_base, rt_kmem_v2p((void *)vdso_info[abi].vdso_code_start), vdso_text_len, 0);

	lwp->vdso_vbase = vdso_base;
	return ret;
}

int arch_setup_additional_pages(struct rt_lwp *lwp)
{
	int ret;

	ret = __setup_additional_pages(VDSO_ABI_AA64, lwp);

	return ret;
}

static void LockVdsoDataPage(VdsoDataPage *vdsoDataPage)
{
    vdsoDataPage->lockCount = 1;
    rt_hw_dmb();
}

static void UnlockVdsoDataPage(VdsoDataPage *vdsoDataPage)
{
    rt_hw_dmb();
    vdsoDataPage->lockCount = 0;
}

void rt_vdso_time_val_update(void)
{
    VdsoDataPage *kVdsoDataPage = vdso_data;

    LockVdsoDataPage(kVdsoDataPage);
    rt_vdso_timeget(kVdsoDataPage);
    UnlockVdsoDataPage(kVdsoDataPage);
}

int RtVdsoInit(void)
{

    if (rt_memcmp(vdso_info[VDSO_ABI_AA64].vdso_code_start, ELF_HEAD, ELF_HEAD_LEN)) {
		rt_kprintf("vDSO is not a valid ELF object!\n");
        return -RT_ERROR;
    }
    vdso_info[VDSO_ABI_AA64].vdso_pages = (
        vdso_info[VDSO_ABI_AA64].vdso_code_end -
        vdso_info[VDSO_ABI_AA64].vdso_code_start) >>
        ARCH_PAGE_SHIFT;

	struct tm time_vdso = SOFT_RTC_TIME_DEFAULT;
	init_vdso_time = timegm(&time_vdso);

    return RT_EOK;
}

INIT_BOARD_EXPORT(RtVdsoInit);
