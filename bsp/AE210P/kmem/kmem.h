#ifndef __KMEM_H__
#define __KMEM_H__

#include <inttypes.h>

#include "list.h"

#define PG_FLAG_FREE    0x00000001


#ifdef CONFIG_PLAT_AE210P
        #include "ae210p_regs.h"
        #define PG_MASK         0xFFFFFF00
        #define PG_SHIFT        8
        #define PG_SIZE         (1 << PG_SHIFT) //256Byte per page

        /* 48MB ~ 112MB */
        #define MEM_START       0x00208000      //EDLM_BASEi+32K
        #define MEM_END         0x00210000      //EDLM_BASE+64K


#elif defined( CONFIG_LATENCY_HEAP )
	#define PG_MASK		0xFFFFFFC0
	#define PG_SHIFT	6
	#define PG_SIZE		(1 << PG_SHIFT)
	#define MEM_START	0x0C000
	#define MEM_END		0x10000
#else
	#ifdef CONFIG_PLAT_AG101P_16MB
	#define PG_MASK		0xFFFFFF00
	#define PG_SHIFT	8
	#define PG_SIZE		(1 << PG_SHIFT)

	#ifdef CONFIG_SMALL_HEAP
	/* 6MB ~ 7MB*/
	#define MEM_START	0x00600000
	#else
	/* 3MB ~ 7MB*/
	#define MEM_START	0x00300000
	#endif
	#define MEM_END		0x00700000
	#else
	#define PG_MASK		0xFFFFF000
	#define PG_SHIFT	12
	#define PG_SIZE		(1 << PG_SHIFT)

	/* 48MB ~ 112MB */
	#define MEM_START	0x03000000
	#define MEM_END		0x07000000
	#endif
#endif
#define MEM_LIMIT		((MEM_END) - (MEM_START))


struct page_struct {

	struct list_head lru;
	uint32_t flag;
	intptr_t alloc_nr;
};

extern int init_kmem(intptr_t start, intptr_t end);

extern void *alloc_pages(intptr_t pg_req_nr);
extern void *alloc_page(void);
extern void free_pages(void *addr);

extern void *kmalloc(intptr_t size);
extern void kfree(void *addr);
extern struct page_struct *addr_to_pf_des(void *addr);

extern void mem_dump_map(void);

#endif /* __KMEM_H__ */
