#include <mm_page.h>
#include <stdio.h>

#include <rtdbg.h>
#include <mm_aspace.h>
#include <riscv_mmu.h>
#include <ioremap.h>

int page()
{
    char* p = (char*) rt_pages_alloc(0);
    strcpy(p, "Hello World!");
    printf("%s", p);
    rt_pages_free(p, 0);
}

int aspace_map()
{
    dlog_session_start();
    dlog_participant("app");
    dlog_participant("aspace");
    dlog_participant("varea");
    dlog_participant("page");

    struct rt_mm_va_hint hint = {
        .prefer = RT_NULL,
        .map_size = 4,
        .flags = 0,
        .limit_start = rt_ioremap_start,
        .limit_range_size = rt_ioremap_size,
    };

    size_t attr = MMU_MAP_K_DEVICE;

    DLOG(msg, "app", "aspace",
        DLOG_MSG, "rt_aspace_map_phy()");
    void *p;
    rt_aspace_map_phy(&rt_kernel_space, &hint, attr, MM_PA_TO_OFF(0x400000), p);

    dlog_session_stop();

    return 0;
}
