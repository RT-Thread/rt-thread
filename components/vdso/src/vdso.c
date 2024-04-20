#include <rtthread.h>
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

VDSO_DATAPAGE VdsoDataPage g_vdsoDataPage __attribute__((__used__));
static size_t g_vdsoSize; 

static size_t calculate_code_size(char* end, char* start)
{

	RT_ASSERT(end != RT_NULL);
	RT_ASSERT(start != RT_NULL);

    return end - start;
}

int __setup_additional_pages(enum vdso_abi abi, struct rt_lwp *lwp)
{	
	RT_ASSERT(lwp != RT_NULL);
	
	int ret;
	void *vdso_vaddr = RT_NULL;

	size_t flags = MAP_PRIVATE | MAP_ANONYMOUS;
	size_t prot = PROT_READ | PROT_WRITE;
	vdso_vaddr = lwp_mmap2(lwp, RT_NULL, g_vdsoSize, prot, flags, -1, 0);

	if(vdso_vaddr)
	{
		lwp_data_put(lwp, vdso_vaddr, (void *)&__vdso_data_start, g_vdsoSize);
		lwp->vdso_vbase = vdso_vaddr + ARCH_PAGE_SIZE;
		ret = RT_EOK;
	}
	else
	{
		ret = -RT_ERROR;
	}
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

/*!
 * @brief rt_vdso_time_val_update	
 * 更新时间,根据系统时钟中断不断将内核一些数据刷新进VDSO的数据页；
 * @return	
 *
 * @see OsTickHandler 函数
 */
void rt_vdso_time_val_update(void)
{
    VdsoDataPage *kVdsoDataPage = (VdsoDataPage *)(&__vdso_data_start);//获取vdso 数据区

    LockVdsoDataPage(kVdsoDataPage);
    rt_vdso_timeget(kVdsoDataPage);
    UnlockVdsoDataPage(kVdsoDataPage);
}

int RtVdsoInit(void)
{
	g_vdsoSize = calculate_code_size(__vdso_text_end,__vdso_data_start);
    if (rt_memcmp((char *)(&__vdso_text_start), ELF_HEAD, ELF_HEAD_LEN)) {
        LOG_E("Vdos Init Failed!");
        return -RT_ERROR;
    }
    vdso_info[VDSO_ABI_AA64].vdso_pages = (
        vdso_info[VDSO_ABI_AA64].vdso_code_end -
        vdso_info[VDSO_ABI_AA64].vdso_code_start) >>
        ARCH_PAGE_SHIFT;

    return RT_EOK;
}
INIT_BOARD_EXPORT(RtVdsoInit);