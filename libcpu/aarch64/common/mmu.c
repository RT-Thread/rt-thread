#include <mmu.h>
#include <stddef.h>

void mmu_memset(char *dst, char v,  size_t len)
{
    while (len--)
    {
        *dst++ = v;
    }
}

static unsigned char main_tbl[4096] __attribute__((aligned (4096)));
static unsigned char __page_start[4096*10] __attribute__((aligned (4096)));
static unsigned long __page_off = 0;
static unsigned long get_free_page(void) {
    __page_off += 4096;
    return (unsigned long)(__page_start + __page_off - 4096);
}

void mmu_init(void)
{
    unsigned long val64;
    unsigned long val32; //val32不是uint32_t,val32只是表示相关的那个寄存器是32位的

    val64 = 0x007f6eUL;
    __asm__ volatile("msr MAIR_EL1, %0\n dsb sy\n"::"r"(val64));
    __asm__ volatile("mrs %0, MAIR_EL1\n dsb sy\n":"=r"(val64));

    //TCR_EL1
    val32 = (16UL << 0)
        | (0x0UL << 6)
        | (0x0UL << 7)
        | (0x3UL << 8)
        | (0x3UL << 10)
        | (0x2UL << 12)
        | (0x0UL << 14)
        | (0x0UL << 16)
        | (0x0UL << 22)
        | (0x1UL << 23)
        | (0x2UL << 30)
        | (0x1UL << 32)
        | (0x0UL << 35)
        | (0x0UL << 36)
        | (0x0UL << 37)
        | (0x0UL << 38);
    __asm__ volatile("msr TCR_EL1, %0\n"::"r"(val32));
    __asm__ volatile("mrs %0, TCR_EL1\n":"=r"(val32));

    __asm__ volatile("msr TTBR0_EL1, %0\n dsb sy\n"::"r"(main_tbl));
    __asm__ volatile("mrs %0, TTBR0_EL1\n dsb sy\n":"=r"(val64));

    mmu_memset((char *)main_tbl, 0, 4096);
}

void mmu_enable(void)
{
    unsigned long val64;
    unsigned long val32;

    //关闭指令cache
    __asm__ volatile("mrs %0, SCTLR_EL1\n":"=r"(val64));
    val64 &= ~0x1000; //disable I
    __asm__ volatile("dmb sy\n msr SCTLR_EL1, %0\n isb sy\n"::"r"(val64));

    //清除指令cache
    __asm__ volatile("IC IALLUIS\n dsb sy\n isb sy\n");
    //清除tlb
    __asm__ volatile("tlbi vmalle1\n dsb sy\n isb sy\n");

    //SCTLR_EL1, turn on mmu
    __asm__ volatile("mrs %0, SCTLR_EL1\n":"=r"(val32));
    val32 |= 0x1005; //enable mmu, I C M
    __asm__ volatile("dmb sy\n msr SCTLR_EL1, %0\nisb sy\n"::"r"(val32));
}

static int map_single_page_2M(unsigned long* lv0_tbl, unsigned long va, unsigned long pa, unsigned long attr) {
    int level;
    unsigned long* cur_lv_tbl = lv0_tbl;
    unsigned long page;
    unsigned long off;
    int level_shift = 39;

    if (va & (0x200000UL - 1)) {
        return MMU_MAP_ERROR_VANOTALIGN;
    }
    if (pa & (0x200000UL - 1)) {
        return MMU_MAP_ERROR_PANOTALIGN;
    }
    for (level = 0; level < 2; level++) {
        off = (va >> level_shift);
        off &= MMU_LEVEL_MASK;
        if ((cur_lv_tbl[off] & 1) == 0) {
            page = get_free_page();
            if (!page) {
                return MMU_MAP_ERROR_NOPAGE;
            }
            mmu_memset((char *)page, 0, 4096);
            cur_lv_tbl[off] = page | 0x3UL;
        }
        page = cur_lv_tbl[off];
        if (!(page & 0x2)) {
            //is block! error!
            return MMU_MAP_ERROR_CONFLICT;
        }
        cur_lv_tbl = (unsigned long*)(page & 0x0000fffffffff000UL);
        level_shift -= 9;
    }
    attr &= 0xfff0000000000ffcUL;
    pa |= (attr | 0x1UL); //block
    off = (va >> 21);
    off &= MMU_LEVEL_MASK;
    cur_lv_tbl[off] = pa;
    return 0;
}

int armv8_map_2M(unsigned long va, unsigned long pa, int count, unsigned long attr)
{
    int i;
    int ret;

    if (va & (0x200000 - 1))
    {
        return -1;
    }
    if (pa & (0x200000 - 1))
    {
        return -1;
    }
    for (i = 0; i < count; i++)
    {
        ret = map_single_page_2M((unsigned long *)main_tbl, va, pa, attr);
        va += 0x200000;
        pa += 0x200000;
        if (ret != 0)
        {
            return ret;
        }
    }
    return 0;
}


