#include "kmem.h"
#include "slab.h"
#include "debug.h"
#include "hal.h"

static struct page_struct mem_map[MEM_LIMIT >> PG_SHIFT];

static intptr_t kmem_start;
static intptr_t kmem_end;
static intptr_t kmem_size;
static intptr_t kmem_total_pages;
static intptr_t kmem_free_pages;

static inline int pg_is_free(struct page_struct *page)
{
	return page->flag & PG_FLAG_FREE;
}

static inline void *pf_to_addr(intptr_t pg_idx)
{
	return (void*)(kmem_start + (pg_idx << PG_SHIFT));
}

static inline intptr_t addr_to_pf(void *addr)
{
	return (intptr_t)(addr - kmem_start) >> PG_SHIFT;
}

static inline void pg_flag_set(intptr_t start, intptr_t count, uint32_t flag)
{
	while (count-- > 0)
		mem_map[start + count].flag |= flag;
}

static inline void pg_flag_clr(intptr_t start, intptr_t count, uint32_t flag)
{
	while (count-- > 0)
		mem_map[start + count].flag &= ~flag;
}

struct page_struct *addr_to_pf_des(void *addr)
{
	return &mem_map[addr_to_pf(addr)];
}

int init_kmem(intptr_t start, intptr_t end)
{
	extern char *_end;
	if((unsigned int)start < (unsigned int)&_end)
		KPANIC("start and _end are overlap. start:%08x, _end=%08x\n", start, &_end);
	kmem_start		= start & PG_MASK;
	kmem_end		= end & PG_MASK;
	kmem_size		= kmem_end - kmem_start;

	kmem_total_pages	= kmem_size >> PG_SHIFT;
	kmem_free_pages		= kmem_total_pages;

	pg_flag_set(0, kmem_total_pages, PG_FLAG_FREE);

	DEBUG(1, 0, "*************************************************\n");
	DEBUG(1, 0, "*             Initializeing MM                  *\n");
	DEBUG(1, 0, "*************************************************\n");

	DEBUG(1, 1, "Start:0x%08x  End:0x%08x, Size:0x%08x(%dK), Pages:%d\n",
			kmem_start, kmem_end, kmem_size,
			kmem_size >> 10, kmem_total_pages);
#ifdef CONFIG_KMEM_SLAB
	init_cache();
#endif
	return 0;
}

void *alloc_pages(intptr_t pg_req_nr)
{
	intptr_t pg_begin_idx = -1;
	intptr_t pg_found_nr = 0;
	intptr_t i = 0;

	DEBUG(0, 1, "Requesting for %d/%d/%d pages\n",
			pg_req_nr, kmem_free_pages, kmem_total_pages);

	if (kmem_free_pages < pg_req_nr)
		return (void*)0;

	for (i = 0; i < kmem_total_pages; i++) {

		if (!pg_is_free(&mem_map[i])) {

			pg_begin_idx = -1;
			continue;
		}

		if (pg_begin_idx < 0) {

			pg_begin_idx = i;
			pg_found_nr = 1;
		}
		else {
			pg_found_nr++;
		}

		if (pg_found_nr == pg_req_nr) {

			pg_flag_clr(pg_begin_idx, pg_req_nr, PG_FLAG_FREE);
			mem_map[pg_begin_idx].alloc_nr = pg_req_nr;

			kmem_free_pages -= pg_req_nr;

			DEBUG(0, 1, "return mem_map %d pages at [%d]:0x%08x\n",
					pg_req_nr, pg_begin_idx, (intptr_t)pf_to_addr(pg_begin_idx));

			return pf_to_addr(pg_begin_idx);
		}
	}

	return (void*)0;
}

void *alloc_page(void)
{
	return alloc_pages(1);
}

void free_pages(void *addr)
{
	intptr_t idx = addr_to_pf(addr);

	KASSERT(!pg_is_free(&mem_map[idx]))

	pg_flag_set(idx, mem_map[idx].alloc_nr, PG_FLAG_FREE);

	DEBUG(0, 1, "0x:%08x, idx:%d, pages:%d, phy_addr:%08x\n",
			(intptr_t)addr, idx, mem_map[idx].alloc_nr,
			(intptr_t)pf_to_addr(idx));

	kmem_free_pages += mem_map[idx].alloc_nr;
	mem_map[idx].alloc_nr = 0;
}

void *kmalloc(intptr_t size)
{
	void *addr = 0;
	intptr_t pg_req_nr = 0;
	int core_intl = 0;

	core_intl = hal_global_int_ctl(HAL_DISABLE_INTERRUPTS);

	DEBUG(0, 1, "%d bytes at:", size);

#ifdef CONFIG_KMEM_USING_SLAB
	addr = kmem_cache_alloc_gen(size);
	if (addr) {

		DEBUG(0, 0, " 0x%08x\n", (intptr_t)addr);
		hal_global_int_ctl(core_intl);
		return addr;
	}
#endif
	size = (size + (PG_SIZE - 1)) & PG_MASK;
	pg_req_nr = size >> PG_SHIFT;

	if (pg_req_nr <= kmem_free_pages) {

		addr = alloc_pages(pg_req_nr);
		DEBUG(0, 0, " 0x%08x\n", (intptr_t)addr);
	}
	else {
		DEBUG(0, 0, "FAIL:(req:%d, free:%d)\n", pg_req_nr, kmem_free_pages);
	}

	hal_global_int_ctl(core_intl);
	return addr;
}

void kfree(void *addr)
{
	int core_intl = 0;

	core_intl = hal_global_int_ctl(HAL_DISABLE_INTERRUPTS);
#ifdef CONFIG_KMEM_USING_SLAB
	struct page_struct *pg = addr_to_pf_des(addr);
	struct cache_struct *cp = GET_PAGE_CACHE(pg);

	if (cp) {
		DEBUG(0, 1, "0x%08x\n", (intptr_t)addr);
		kmem_cache_free(cp, addr);

		hal_global_int_ctl(core_intl);
		return;
	}
#endif
	DEBUG(0, 1, "0x%08x\n", (intptr_t)addr);

	free_pages(addr);
	hal_global_int_ctl(core_intl);
}

void mem_dump_map(void)
{
	intptr_t i;

	DEBUG(1, 1, "*:free +: begin of allocated chunk, -:allocated\n");

	for (i = 0; i < kmem_total_pages; i++) {

		if (i%32 == 0)
			DEBUG(1, 0, "\n0x%08x\t: ", kmem_start + i * PG_SIZE);
		else if (i%8 == 0)
			DEBUG(1, 0, "  ");

		if (pg_is_free(&mem_map[i]))
			DEBUG(1, 0, "*");
		else if (mem_map[i].alloc_nr)
			DEBUG(1, 0, "+");
		else
			DEBUG(1, 0, "-");
	}

	DEBUG(1, 0, "\n");
}
