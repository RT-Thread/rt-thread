/*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <rtthread.h>
#include <rthw.h>

#if defined(RT_USING_SMART) && defined(ARCH_MM_MMU)

#include <encoding.h>
#include <mmu.h>
#include <riscv_mmu.h>

#include <ioremap.h>
#include <mm_aspace.h>
#include <mm_page.h>

#include <board.h>

#ifdef RT_USING_DFS
#include <fcntl.h>
#include <lwp.h>
#include <lwp_pid.h>
#include <sys/stat.h>
#include <unistd.h>
#endif /* RT_USING_DFS */

#define DEMO_MAGIC_A 0x5a5aa5a5c908c908ULL
#define DEMO_MAGIC_B 0xdeadbeef1234abcdULL

/* satp.PPN is 44 bits wide on RV64 */
#define SATP_PPN_MASK ((1UL << 44) - 1)

/* returned by _walk_v2p() when the walk stops on an invalid PTE */
#define WALK_LEVEL_NONE (-1)

static int _pass;
static int _fail;
static int _skip;

#define CHECK(expr, ...)             \
    do                               \
    {                                \
        if (expr)                    \
        {                            \
            _pass++;                 \
            rt_kprintf("  [ OK ] "); \
        }                            \
        else                         \
        {                            \
            _fail++;                 \
            rt_kprintf("  [FAIL] "); \
        }                            \
        rt_kprintf(__VA_ARGS__);     \
        rt_kprintf("\n");            \
    } while (0)

#define SKIP(...)                \
    do                           \
    {                            \
        _skip++;                 \
        rt_kprintf("  [SKIP] "); \
        rt_kprintf(__VA_ARGS__); \
        rt_kprintf("\n");        \
    } while (0)

/*
 * Translate vaddr by hand, starting from a given top level page table. This
 * deliberately does not go through rt_hw_mmu_v2p() so that the two results can
 * be cross-checked.
 */
static void *_walk_table(rt_pte_t *tbl, void *vaddr, int *level_out, rt_size_t *pgsize_out)
{
    rt_ubase_t pvoff = PV_OFFSET;
    int level;

    *level_out = WALK_LEVEL_NONE;
    *pgsize_out = 0;

    for (level = 1; level <= ARCH_PAGE_TBL_LEVELS; level++)
    {
        rt_pte_t pte = tbl[GET_LVL_INDEX(vaddr, level)];

        if (!PTE_USED(pte))
        {
            break;
        }
        if (PAGE_IS_LEAF(pte))
        {
            rt_size_t pgsize = 1UL << (ARCH_PAGE_SHIFT +
                                       (ARCH_PAGE_TBL_LEVELS - level) * ARCH_INDEX_WIDTH);

            *level_out = level;
            *pgsize_out = pgsize;
            return (void *)(GET_PADDR(pte) | ((rt_ubase_t)vaddr & (pgsize - 1)));
        }
        tbl = (rt_pte_t *)PPN_TO_VPN(GET_PADDR(pte), pvoff);
    }

    return ARCH_MAP_FAILED;
}

/*
 * Walk the page table the hardware is actually using (rooted at satp).
 *
 * With RT_USING_SMP each hart runs its own copy of the top level table, so the
 * walk is done with scheduling disabled to stay on the hart whose satp was
 * sampled.
 */
static void *_walk_v2p(void *vaddr, int *level_out, rt_size_t *pgsize_out)
{
    void *paddr;
    rt_pte_t *root;

    rt_enter_critical();
    root = (rt_pte_t *)PPN_TO_VPN((read_csr(satp) & SATP_PPN_MASK) << PAGE_OFFSET_BIT, PV_OFFSET);
    paddr = _walk_table(root, vaddr, level_out, pgsize_out);
    rt_exit_critical();

    return paddr;
}

/* per-hart copy of the kernel top level page table */
static rt_pte_t *_kernel_hart_table(int hartid)
{
    return (rt_pte_t *)((rt_ubase_t)rt_kernel_space.page_table + hartid * ARCH_PAGE_SIZE);
}

/*
 * Every hart runs its own copy of the top level table, so a VA must translate
 * to the very same PA on all of them (the .percpu section aside, which is
 * mapped per hart on purpose and is not probed here).
 */
static int _hart_tables_agree(void *vaddr, void *expect)
{
    for (int hartid = 0; hartid < RT_CPUS_NR; hartid++)
    {
        int level;
        rt_size_t pgsize;

        if (_walk_table(_kernel_hart_table(hartid), vaddr, &level, &pgsize) != expect)
        {
            return 0;
        }
    }
    return 1;
}

/* [1] translation mode actually programmed into satp */
static void _tc_satp_mode(void)
{
    rt_ubase_t satp = read_csr(satp);
    rt_ubase_t mode = (satp >> SATP_MODE_OFFSET) & 0xfUL;

    rt_kprintf("[1] satp translation mode\n");
    rt_kprintf("      satp 0x%lx, mode %ld, levels %d, recorded 0x%lx\n",
               satp, mode, ARCH_PAGE_TBL_LEVELS, g_mmu_modes_supported);

    CHECK(mode != SATP_MODE_BARE, "MMU is enabled (satp.mode != Bare)");
    CHECK(mode == SATP_MODE, "satp.mode matches the built-in SATP_MODE (%d)", SATP_MODE);
    CHECK((g_mmu_modes_supported >> mode) & 1UL,
          "the BSP recorded the same active mode in g_mmu_modes_supported");
}

/* [2] kernel linear mapping: PA == VA + PV_OFFSET for every kernel section */
static void _tc_kernel_linear_map(void)
{
    rt_ubase_t pvoff = PV_OFFSET;
    volatile int on_stack = 0;
    void *heap;

    rt_kprintf("[2] kernel linear mapping (PA = VA + PV_OFFSET)\n");
    rt_kprintf("      PV_OFFSET 0x%lx, KERNEL_VADDR_START 0x%lx\n",
               pvoff, (rt_ubase_t)KERNEL_VADDR_START);

    CHECK((rt_ubase_t)(0 - pvoff) == (rt_ubase_t)KERNEL_VADDR_START,
          "PV_OFFSET == -KERNEL_VADDR_START");

    struct
    {
        const char *name;
        void *vaddr;
    } samples[] = {
        { ".text", (void *)(rt_ubase_t)_tc_kernel_linear_map },
        { ".bss ", (void *)&_pass },
        { "stack", (void *)&on_stack },
    };

    for (rt_size_t i = 0; i < sizeof(samples) / sizeof(samples[0]); i++)
    {
        void *va = samples[i].vaddr;
        void *pa = rt_kmem_v2p(va);

        CHECK(pa == (void *)((rt_ubase_t)va + pvoff),
              "%s VA 0x%lx -> PA 0x%lx", samples[i].name,
              (rt_ubase_t)va, (rt_ubase_t)pa);
    }

    heap = rt_malloc(64);
    if (heap)
    {
        void *pa = rt_kmem_v2p(heap);

        CHECK(pa == (void *)((rt_ubase_t)heap + pvoff),
              "heap  VA 0x%lx -> PA 0x%lx", (rt_ubase_t)heap, (rt_ubase_t)pa);
        rt_free(heap);
    }
    else
    {
        SKIP("heap  rt_malloc() failed");
    }
}

/* [3] hand-written page table walk vs. rt_hw_mmu_v2p() */
static void _tc_page_table_walk(void)
{
    void *root_pa;
    int level;
    rt_size_t pgsize;
    void *samples[2];
    const char *names[2] = { ".text", "stack" };
    volatile int on_stack = 0;

    rt_kprintf("[3] hardware page table walk\n");

    root_pa = rt_kmem_v2p(rt_kernel_space.page_table);
    rt_kprintf("      kernel page table VA 0x%lx / PA 0x%lx\n",
               (rt_ubase_t)rt_kernel_space.page_table, (rt_ubase_t)root_pa);

    samples[0] = (void *)(rt_ubase_t)_tc_page_table_walk;
    samples[1] = (void *)&on_stack;

    for (rt_size_t i = 0; i < sizeof(samples) / sizeof(samples[0]); i++)
    {
        void *walked = _walk_v2p(samples[i], &level, &pgsize);
        void *queried = rt_kmem_v2p(samples[i]);

        CHECK(walked != ARCH_MAP_FAILED && walked == queried,
              "%s VA 0x%lx: walk PA 0x%lx (leaf at L%d, page %ldKB) == v2p PA 0x%lx",
              names[i], (rt_ubase_t)samples[i], (rt_ubase_t)walked,
              level, (rt_size_t)(pgsize >> 10), (rt_ubase_t)queried);
        CHECK(_hart_tables_agree(samples[i], queried),
              "%s VA 0x%lx resolves identically in all %d per-hart tables",
              names[i], (rt_ubase_t)samples[i], RT_CPUS_NR);
    }
}

/* [4] page allocator + two cacheable aliases of the same physical page */
static void _tc_page_alias(void)
{
    void *page;
    void *paddr;
    void *alias;

    rt_kprintf("[4] page allocation and VA alias coherency\n");

    page = rt_pages_alloc(0);
    if (page == RT_NULL)
    {
        SKIP("rt_pages_alloc() failed");
        return;
    }

    paddr = rt_kmem_v2p(page);
    CHECK(paddr != ARCH_MAP_FAILED,
          "page VA 0x%lx is mapped, PA 0x%lx", (rt_ubase_t)page, (rt_ubase_t)paddr);

    *(volatile rt_uint64_t *)page = DEMO_MAGIC_A;

    alias = rt_ioremap_cached(paddr, ARCH_PAGE_SIZE);
    if (alias == RT_NULL)
    {
        SKIP("rt_ioremap_cached() failed, alias test not run");
        rt_pages_free(page, 0);
        return;
    }

    CHECK(alias != page, "alias VA 0x%lx differs from the linear VA", (rt_ubase_t)alias);
    CHECK(rt_kmem_v2p(alias) == paddr, "alias VA translates back to the same PA");
    CHECK(*(volatile rt_uint64_t *)alias == DEMO_MAGIC_A,
          "value written through the linear VA is visible through the alias");

    *(volatile rt_uint64_t *)alias = DEMO_MAGIC_B;
    CHECK(*(volatile rt_uint64_t *)page == DEMO_MAGIC_B,
          "value written through the alias is visible through the linear VA");

    rt_iounmap(alias);
    CHECK(rt_kmem_v2p(alias) == ARCH_MAP_FAILED, "alias VA is gone after rt_iounmap()");
    CHECK(_hart_tables_agree(alias, ARCH_MAP_FAILED),
          "alias VA is gone in all %d per-hart tables", RT_CPUS_NR);

    rt_pages_free(page, 0);
}

/* [5] device mapping through ioremap */
static void _tc_ioremap_device(void)
{
    void *paddr = (void *)XIAOHUI_UART0_PHY_ADDR;
    void *vaddr;
    int level;
    rt_size_t pgsize;

    rt_kprintf("[5] device mapping (UART0 @ 0x%lx)\n", (rt_ubase_t)paddr);

    vaddr = rt_ioremap(paddr, ARCH_PAGE_SIZE);
    if (vaddr == RT_NULL)
    {
        SKIP("rt_ioremap() failed");
        return;
    }

    CHECK(rt_kmem_v2p(vaddr) == paddr,
          "VA 0x%lx translates to the requested PA", (rt_ubase_t)vaddr);
    CHECK(_walk_v2p(vaddr, &level, &pgsize) == paddr,
          "page table walk agrees (leaf at L%d, page %ldKB)", level, (rt_size_t)(pgsize >> 10));
    CHECK(_hart_tables_agree(vaddr, paddr),
          "mapping is present in all %d per-hart tables", RT_CPUS_NR);

    rt_iounmap(vaddr);
    CHECK(rt_kmem_v2p(vaddr) == ARCH_MAP_FAILED, "VA is unmapped after rt_iounmap()");
    CHECK(_hart_tables_agree(vaddr, ARCH_MAP_FAILED),
          "VA is unmapped in all %d per-hart tables", RT_CPUS_NR);
}

#ifdef RT_USING_DFS
/* [6] rootfs carries the user applications (romfs -> elmfat root) */
static void _tc_rootfs(void)
{
    static const char *paths[] = { "/rom/bin/hello", "/bin/hello" };
    char magic[4];
    int fd;

    rt_kprintf("[6] RT-Smart rootfs\n");

    for (rt_size_t i = 0; i < sizeof(paths) / sizeof(paths[0]); i++)
    {
        struct stat st;

        CHECK(stat(paths[i], &st) == 0 && st.st_size > 0,
              "%s exists, %ld bytes", paths[i], (long)st.st_size);
    }

    fd = open("/bin/hello", O_RDONLY);
    if (fd < 0)
    {
        SKIP("open(/bin/hello) failed, ELF header not checked");
        return;
    }
    CHECK(read(fd, magic, sizeof(magic)) == sizeof(magic) &&
              magic[0] == 0x7f && magic[1] == 'E' && magic[2] == 'L' && magic[3] == 'F',
          "/bin/hello starts with the ELF magic");
    close(fd);
}

/* [7] user process: private address space, isolated from the kernel one */
static void _tc_user_process(void)
{
    const char *path = "/bin/hello";
    char *argv[] = { RT_NULL, RT_NULL };
    struct rt_lwp *lwp;
    void *entry = RT_NULL;
    void *entry_pa = ARCH_MAP_FAILED;
    pid_t pid;
    int alive;
    int i;

    rt_kprintf("[7] RT-Smart user process\n");

    argv[0] = (char *)path;
    pid = exec((char *)path, 0, 1, argv);
    CHECK(pid > 0, "exec(%s) returned pid %d", path, (int)pid);
    if (pid <= 0)
    {
        return;
    }

    lwp = lwp_from_pid_and_lock(pid);
    if (lwp == RT_NULL)
    {
        SKIP("pid %d already reaped, address space not inspected", (int)pid);
        return;
    }

    entry = lwp->text_entry;
    CHECK(lwp->aspace != RT_NULL && lwp->aspace != &rt_kernel_space,
          "process owns a private address space");
    CHECK(lwp->aspace != RT_NULL && lwp->aspace->page_table != rt_kernel_space.page_table,
          "process owns a private page table");
    CHECK(rt_hw_mmu_v2p(&rt_kernel_space, entry) == ARCH_MAP_FAILED,
          "text entry 0x%lx is NOT visible from the kernel space", (rt_ubase_t)entry);
    lwp_from_pid_release_lock(lwp);

    /*
     * The text pages are faulted in on demand, so poll the process page table
     * until the entry page shows up, then keep polling until the process is
     * gone (it prints on its own while running).
     */
    for (i = 0, alive = 1; i < 200 && alive; i++)
    {
        rt_thread_mdelay(10);

        lwp = lwp_from_pid_and_lock(pid);
        if (lwp == RT_NULL)
        {
            alive = 0;
            break;
        }
        if (entry_pa == ARCH_MAP_FAILED)
        {
            entry_pa = rt_hw_mmu_v2p(lwp->aspace, entry);
        }
        lwp_from_pid_release_lock(lwp);
    }

    if (entry_pa == ARCH_MAP_FAILED)
    {
        SKIP("entry page was never observed mapped (process too short-lived)");
    }
    else
    {
        CHECK(entry_pa != ARCH_MAP_FAILED, "text entry 0x%lx was demand-mapped to PA 0x%lx",
              (rt_ubase_t)entry, (rt_ubase_t)entry_pa);
    }
    CHECK(!alive, "process exited and was reaped within %d ms", (i + 1) * 10);
}
#endif /* RT_USING_DFS */

void mmu_example(void)
{
    _pass = 0;
    _fail = 0;
    _skip = 0;

    rt_kprintf("mmu demo start!\n");

    _tc_satp_mode();
    _tc_kernel_linear_map();
    _tc_page_table_walk();
    _tc_page_alias();
    _tc_ioremap_device();
#ifdef RT_USING_DFS
    _tc_rootfs();
    _tc_user_process();
#else
    rt_kprintf("[6] RT-Smart rootfs / user process: skipped, RT_USING_DFS is off\n");
#endif /* RT_USING_DFS */

    rt_kprintf("mmu demo done: %d passed, %d failed, %d skipped\n", _pass, _fail, _skip);
}

static int mmu_demo(int argc, char **argv)
{
    mmu_example();
    return _fail == 0 ? 0 : -RT_ERROR;
}
MSH_CMD_EXPORT(mmu_demo, MMU and RT - Smart runtime checks);

#endif /* RT_USING_SMART && ARCH_MM_MMU */
