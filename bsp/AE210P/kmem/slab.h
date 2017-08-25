#ifndef __SLAB_H__
#define __SLAB_H__

#include <inttypes.h>
#include "list.h"

#define BUFCTL_END      (((bufctl_t)(~0U))-0)
#define BUFCTL_FREE     (((bufctl_t)(~0U))-1)
#define SLAB_LIMIT      (((bufctl_t)(~0U))-2)

#define CACHE_NAME_BUF_SIZE 20

struct cache_struct;

typedef void (*handler_t)(void *, struct cache_struct*, intptr_t);

struct cache_struct {

	struct list_head slab_full;
	struct list_head slab_partial;
	struct list_head slab_free;
	struct list_head next;
	char name[CACHE_NAME_BUF_SIZE];
	intptr_t obj_size;
	intptr_t page_nr;
	intptr_t num;
	intptr_t free_objs;
	intptr_t total_objs;
	handler_t ctor;
	handler_t dtor;
};

struct slab_struct {

	struct cache_struct *cache;
	struct list_head list;

	void *s_mem;
	int ref_cnt;
	intptr_t next_free;
};

typedef intptr_t *bufctl_t;

extern struct cache_struct *kmem_cache_create(const char *name, intptr_t obj_size, handler_t ctor, handler_t dtor);
extern void *kmem_cache_alloc(struct cache_struct *cp);
extern void kmem_cache_free(struct cache_struct *cp, void *buf_addr);
extern void *kmem_cache_alloc_gen(intptr_t size);
extern void kmem_cache_destory(struct cache_struct *cp);
extern void kmem_cache_reap(struct cache_struct *cp);
extern void init_cache(void);
extern void init_general_caches(void);

#define SET_PAGE_CACHE(pg,x)  ((pg)->lru.next = (struct list_head*)(x))
#define GET_PAGE_CACHE(pg)    ((struct cache_struct*)(pg)->lru.next)
#define SET_PAGE_SLAB(pg,x)   ((pg)->lru.prev = (struct list_head*)(x))
#define GET_PAGE_SLAB(pg)     ((struct slab_struct*)(pg)->lru.prev)

#endif /* __SLAB_H__ */
