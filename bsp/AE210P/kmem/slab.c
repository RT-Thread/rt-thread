#include "list.h"
#include "slab.h"

#include "kmem.h"
#include "debug.h"

#include <string.h>

LIST_HEAD(cache_list);
struct cache_struct *cachep;
struct cache_struct *slabp;

struct cache_struct *kmem_cache_create(const char *name, intptr_t obj_size, handler_t ctor, handler_t dtor)
{
	struct cache_struct *cp;

	cp = kmem_cache_alloc(cachep);
	KASSERT(cp);

	strncpy(cp->name, name, CACHE_NAME_BUF_SIZE-1);
	cp->obj_size	= obj_size;
	cp->page_nr	= obj_size * 8 / PG_SIZE + 1;
	cp->ctor	= ctor;
	cp->dtor	= dtor;
	cp->free_objs	= 0;

	if (cp->obj_size < (PG_SIZE >> 3))
		cp->num = (PG_SIZE - sizeof(struct slab_struct)) / (sizeof(bufctl_t) + cp->obj_size);
	else
		cp->num = PG_SIZE / cp->obj_size;

	cp->total_objs = 0;

	INIT_LIST_HEAD(&cp->slab_full);
	INIT_LIST_HEAD(&cp->slab_partial);
	INIT_LIST_HEAD(&cp->slab_free);
	INIT_LIST_HEAD(&cp->next);

	list_add_tail(&cp->next, &cache_list);

	DEBUG(0, 1, "Cache \"%s\" (size:%d) created\n", name, obj_size);

	return cp;
}

static inline bufctl_t *slab_bufctl(struct slab_struct *sp)
{
	return (bufctl_t*)(sp+1);
}

static void cache_init_objs(struct cache_struct *cp, struct slab_struct *sp, unsigned long ctor_flags)
{
	intptr_t i;

	DEBUG(0, 1, " %s:cp->num =%d\n", cp->name, cp->num);

	for (i = 0; i < cp->num; i++) {

		void *objp = (void*)(sp->s_mem + cp->obj_size*i);

		if (cp->ctor)
			cp->ctor(objp, cp, ctor_flags);

		slab_bufctl(sp)[i] = (bufctl_t)(i+1);
	}

	slab_bufctl(sp)[i-1] = (bufctl_t)BUFCTL_END;
	sp->next_free = 0;
}

static void kmem_cache_grow(struct cache_struct *cp)
{
	void *addr;
	struct slab_struct *sp;
	struct page_struct *pg_des;
	int i;

	addr = alloc_pages(cp->page_nr);
	KASSERT(addr);

	if (cp->obj_size < (PG_SIZE >> 3)) {

		sp = (struct slab_struct*)addr;
		sp->s_mem = (void*)sp + sizeof(struct slab_struct) +  sizeof(bufctl_t)*cp->num;
	}
	else {
		sp = (struct slab_struct*)kmem_cache_alloc(slabp);
		KASSERT(sp);

		sp->s_mem = addr;
	}

	pg_des = addr_to_pf_des(addr);

	i = cp->page_nr;
	while (i--) {

		SET_PAGE_CACHE(pg_des, cp);
		SET_PAGE_SLAB(pg_des, sp);
		pg_des++;
	}

	sp->cache = cp;
	sp->ref_cnt = 0;

	cache_init_objs(cp, sp, 0);
	cp->free_objs += cp->num;
	cp->total_objs += cp->num;

	INIT_LIST_HEAD(&sp->list);
	list_add_tail(&sp->list, &cp->slab_free);

	DEBUG(0, 1, " %s:grow up, get %d more free object\n", cp->name, cp->free_objs);
}

static void *kmem_slab_refill(struct slab_struct *sp)
{
	void *buf_addr;
	intptr_t idx;

	idx = sp->next_free;
	sp->next_free = (intptr_t)(slab_bufctl(sp)[idx]);
	slab_bufctl(sp)[idx] = BUFCTL_END;

	DEBUG(0, 1, " %s:allocating %uth obj in a slab of Cache \n", sp->cache->name, idx);

	if (sp->next_free == (intptr_t)BUFCTL_END) {

		DEBUG(0, 1, " %s:move from slab_partial to slab_full\n", sp->cache->name);
		list_move(&sp->list, &sp->cache->slab_full);
	}
	else if (sp->ref_cnt == 0) {

		DEBUG(0, 1, " %s:move from slab_free to slab_partial\n", sp->cache->name);
		list_move(&sp->list, &sp->cache->slab_partial);
	}

	sp->ref_cnt++;
	sp->cache->free_objs--;
	buf_addr = sp->s_mem + idx*sp->cache->obj_size;

	return buf_addr;
}

static void slab_print_list(struct cache_struct *cp)
{
	DEBUG(0, 1, " %s:partial[%c], free[%c], full[%c] %3d/%3d (%3d)\n",
			cp->name,
			list_empty(&cp->slab_partial)?' ':'*',
			list_empty(&cp->slab_free)?' ':'*',
			list_empty(&cp->slab_full)?' ':'*',
			cp->free_objs,
			cp->total_objs,
			cp->num);
}

void *kmem_cache_alloc(struct cache_struct *cp)
{
	struct slab_struct *sp;

	slab_print_list(cp);
	DEBUG(0, 1, " %s:free_objs  = %d/%d\n", cp->name, cp->free_objs, cp->num);

	while (!cp->free_objs)
		kmem_cache_grow(cp);

	list_for_each_entry(sp, &cp->slab_partial, list) {

		DEBUG(0, 1, " %s:get a free obj from slab_partial list\n", cp->name);
		return kmem_slab_refill(sp);
	}

	list_for_each_entry(sp, &cp->slab_free, list) {

		DEBUG(0, 1, " %s:get a free obj from slab_free list\n", cp->name);
		return kmem_slab_refill(sp);
	}

	KPANIC("%s:failed to alloc a free slab\n", cp->name);
}

void kmem_cache_free(struct cache_struct *cp, void *buf_addr)
{
	struct page_struct *pg;
	struct slab_struct *sp;
	intptr_t idx;

	pg = addr_to_pf_des(buf_addr);
	sp = GET_PAGE_SLAB(pg);

	idx = ((intptr_t)(buf_addr - sp->s_mem)) / cp->obj_size;

	slab_bufctl(sp)[idx] = (bufctl_t)sp->next_free;
	sp->next_free = idx;

	DEBUG(0, 1, " %s:freeing %uth obj in a slab\n", cp->name, idx);

	if (sp->ref_cnt == cp->num) {

		DEBUG(0, 1, " %s:move from slab_full to slab_partial\n", cp->name);
		list_move(&sp->list, &sp->cache->slab_partial);
	}
	else if (sp->ref_cnt == 1) {

		DEBUG(0, 1, " %s:move from slab_partial to slab_free\n", cp->name);
		list_move(&sp->list, &sp->cache->slab_free);
	}

	cp->free_objs++;
	sp->ref_cnt--;
}

void kmem_cache_destory(struct cache_struct *cp)
{
	if (!cp)
		return;
}

void kmem_cache_reap(struct cache_struct *cp)
{
	struct slab_struct *sp, *tmp;

	slab_print_list(cp);

	list_for_each_entry_safe(sp, tmp, &cp->slab_free, list) {

		list_del(&sp->list);

		if (cp->obj_size < (PG_SIZE >> 3))

			free_pages(sp);
		else
			free_pages(sp->s_mem);

		cp->free_objs -= cp->num;

		DEBUG(0, 1, " %s:cache shrink, free_objs = %d\n", cp->name, cp->free_objs);
	}
}

void init_cache(void)
{
        DEBUG(1, 0, "*************************************************\n");
        DEBUG(1, 0, "*             Initializeing SLAB                *\n");
        DEBUG(1, 0, "*************************************************\n");

	/* Initialize the cachep statically */
	cachep = (struct cache_struct*)alloc_page();
	KASSERT(cachep);

	strncpy(cachep->name, "cachep", CACHE_NAME_BUF_SIZE-1);

	cachep->obj_size	= sizeof(struct cache_struct);
	cachep->page_nr		= sizeof(struct cache_struct) * 8 / PG_SIZE + 1;
	cachep->ctor		= (void*)0;
	cachep->dtor		= (void*)0;
	cachep->num		= (PG_SIZE - sizeof(struct slab_struct)) / (sizeof(bufctl_t) + cachep->obj_size);
	cachep->free_objs	= 0;
	cachep->total_objs	= 0;

	INIT_LIST_HEAD(&cachep->slab_full);
	INIT_LIST_HEAD(&cachep->slab_partial);
	INIT_LIST_HEAD(&cachep->slab_free);
	INIT_LIST_HEAD(&cachep->next);

	list_add_tail(&cachep->next, &cache_list);

	slabp = kmem_cache_create("slabp", sizeof(struct cache_struct), (void*)0, (void*)0);

#ifdef CONFIG_KMEM_USING_SLAB
	init_general_caches();
#endif
}

#define TBL_SIZE	10
#define MIN_OBJ_SIZE	8

struct cache_tbl_entry {

	struct cache_struct *cp;
	intptr_t size;
};

struct cache_tbl_entry cache_tbl[TBL_SIZE];

void init_general_caches(void)
{
	char name_buf[CACHE_NAME_BUF_SIZE];
	intptr_t size;
	intptr_t i;

	size = MIN_OBJ_SIZE;

        DEBUG(1, 0, "*************************************************\n");
        DEBUG(1, 0, "*   Initializeing SLAB(General Object Caches)   *\n");
        DEBUG(1, 0, "*************************************************\n");

	for (i = 0; i < TBL_SIZE; i++) {

		sprintf(name_buf, "gen_cache_%d", size);
		cache_tbl[i].cp = kmem_cache_create(name_buf, size, (void*)0, (void*)0);
		cache_tbl[i].size = size;
		size *= 2;
	}
}

void *kmem_cache_alloc_gen(intptr_t size)
{
	int i;

	for (i = 0; i < TBL_SIZE; i++) {

		if (cache_tbl[i].size > size)
			return kmem_cache_alloc(cache_tbl[i].cp);
	}

	return (void*)0;
}
