/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-10-12     Jesven       first version
 * 2023-02-20     wangxiaoyao  adapt to mm
 */
#include <rthw.h>
#include <rtthread.h>

#ifdef ARCH_MM_MMU
#include <lwp.h>
#include <lwp_shm.h>
#include <lwp_mm.h>

#include <lwp_user_mm.h>
#include <mmu.h>

/* the kernel structure to represent a share-memory */
struct lwp_shm_struct
{
    struct rt_mem_obj mem_obj;
    size_t addr;    /* point to the next item in the free list when not used */
    size_t size;
    int    ref;
    size_t key;
};

static struct lwp_avl_struct *shm_tree_key;
static struct lwp_avl_struct *shm_tree_pa;

static int shm_free_list = -1;  /* the single-direct list of freed items */
static int shm_id_used = 0;     /* the latest allocated item in the array */
static struct lwp_shm_struct _shm_ary[RT_LWP_SHM_MAX_NR];

static const char *get_shm_name(rt_varea_t varea)
{
    return "user.shm";
}

static void on_shm_varea_open(struct rt_varea *varea)
{
    struct lwp_shm_struct *shm;
    shm = rt_container_of(varea->mem_obj, struct lwp_shm_struct, mem_obj);
    shm->ref += 1;
}

static void on_shm_varea_close(struct rt_varea *varea)
{
    struct lwp_shm_struct *shm;
    shm = rt_container_of(varea->mem_obj, struct lwp_shm_struct, mem_obj);
    shm->ref -= 1;
}

static void on_shm_page_fault(struct rt_varea *varea, struct rt_aspace_fault_msg *msg)
{
    struct lwp_shm_struct *shm;
    int err;
    shm = rt_container_of(varea->mem_obj, struct lwp_shm_struct, mem_obj);

    /* map all share page frames to user space in a time */
    void *page = (void *)shm->addr;
    void *pg_paddr = (char *)page + PV_OFFSET;
    err = rt_varea_map_range(varea, varea->start, pg_paddr, shm->size);

    if (err == RT_EOK)
    {
        msg->response.status = MM_FAULT_STATUS_OK_MAPPED;
        msg->response.size = shm->size;
        msg->response.vaddr = page;
    }

    return ;
}

/*
 * Try to allocate an structure 'lwp_shm_struct' from the freed list or the
 * static array.
 */
static int _shm_id_alloc(void)
{
    int id = -1;

    if (shm_free_list != -1)    /* first try the freed list */
    {
        id = shm_free_list;
        shm_free_list = (int)_shm_ary[shm_free_list].addr;  /* single-direction */
    }
    else if (shm_id_used < RT_LWP_SHM_MAX_NR)   /* then try the array */
    {
        id = shm_id_used;
        shm_id_used++;
    }
    return id;
}

/* Release the item in the static array to the freed list. */
static void shm_id_free(int id)
{
    /* link the freed itme to the single-direction list */
    _shm_ary[id].addr = (size_t)shm_free_list;
    shm_free_list = id;
}

/* Locate the shared memory through 'key' or create a new one. */
static int _lwp_shmget(size_t key, size_t size, int create)
{
    int id = -1;
    struct lwp_avl_struct *node_key = 0;
    struct lwp_avl_struct *node_pa = 0;
    void *page_addr = 0;
    uint32_t bit = 0;

    /* try to locate the item with the key in the binary tree */
    node_key = lwp_avl_find(key, shm_tree_key);
    if (node_key)
    {
        return (struct lwp_shm_struct *)node_key->data - _shm_ary;   /* the index */
    }

    /* If there doesn't exist such an item and we're allowed to create one ... */
    if (create)
    {
        struct lwp_shm_struct* p;

        if (!size)
        {
            goto err;
        }

        id = _shm_id_alloc();
        if (id == -1)
        {
            goto err;
        }

        /* allocate pages up to 2's exponent to cover the required size */
        bit = rt_page_bits(size);
        page_addr = rt_pages_alloc_ext(bit, PAGE_ANY_AVAILABLE);   /* virtual address */
        if (!page_addr)
        {
            goto err;
        }

        /* initialize the shared memory structure */
        p = _shm_ary + id;
        p->addr = (size_t)page_addr;
        p->size = (1UL << (bit + ARCH_PAGE_SHIFT));
        p->ref = 0;
        p->key = key;
        p->mem_obj.get_name = get_shm_name;
        p->mem_obj.on_page_fault = on_shm_page_fault;
        p->mem_obj.on_varea_open = on_shm_varea_open;
        p->mem_obj.on_varea_close = on_shm_varea_close;
        p->mem_obj.hint_free = NULL;

        /* then insert it into the balancing binary tree */
        node_key = (struct lwp_avl_struct *)rt_malloc(sizeof(struct lwp_avl_struct) * 2);
        if (!node_key)
        {
            goto err;
        }
        node_key->avl_key = p->key;
        node_key->data = (void *)p;
        lwp_avl_insert(node_key, &shm_tree_key);
        node_pa = node_key + 1;
        node_pa->avl_key = p->addr;
        node_pa->data = (void *)p;
        lwp_avl_insert(node_pa, &shm_tree_pa);
    }
    return id;

err:
    if (id != -1)
    {
        shm_id_free(id);
    }
    if (page_addr)
    {
        rt_pages_free(page_addr, bit);
    }
    if (node_key)
    {
        rt_free(node_key);
    }
    return -1;
}

/* A wrapping function, get the shared memory with interrupts disabled. */
int lwp_shmget(size_t key, size_t size, int create)
{
    int ret = 0;

    rt_mm_lock();
    ret = _lwp_shmget(key, size, create);
    rt_mm_unlock();
    return ret;
}

/* Locate the binary tree node_key corresponding to the shared-memory id. */
static struct lwp_avl_struct *shm_id_to_node(int id)
{
    struct lwp_avl_struct *node_key = 0;
    struct lwp_shm_struct *p = RT_NULL;

    /* check id */
    if (id < 0 || id >= RT_LWP_SHM_MAX_NR)
    {
        return RT_NULL;
    }

    p = _shm_ary + id;      /* the address of the shared-memory structure */
    node_key = lwp_avl_find(p->key, shm_tree_key);
    if (!node_key)
    {
        return RT_NULL;
    }
    if (node_key->data != (void *)p)
    {
        return RT_NULL;
    }
    return node_key;
}

/* Free the shared pages, the shared-memory structure and its binary tree node_key. */
static int _lwp_shmrm(int id)
{
    struct lwp_avl_struct *node_key = RT_NULL;
    struct lwp_avl_struct *node_pa = RT_NULL;
    struct lwp_shm_struct* p = RT_NULL;
    uint32_t bit = 0;

    node_key = shm_id_to_node(id);
    if (!node_key)
    {
        return -1;
    }
    p = (struct lwp_shm_struct *)node_key->data;
    if (p->ref)
    {
        return 0;
    }
    bit = rt_page_bits(p->size);
    rt_pages_free((void *)p->addr, bit);
    lwp_avl_remove(node_key, &shm_tree_key);
    node_pa = node_key + 1;
    lwp_avl_remove(node_pa, &shm_tree_pa);
    rt_free(node_key);
    shm_id_free(id);
    return 0;
}

/* A wrapping function, free the shared memory with interrupt disabled. */
int lwp_shmrm(int id)
{
    int ret = 0;

    ret = _lwp_shmrm(id);

    return ret;
}

/* Map the shared memory specified by 'id' to the specified virtual address. */
static void *_lwp_shmat(int id, void *shm_vaddr)
{
    int err;
    struct rt_lwp *lwp  = RT_NULL;
    struct lwp_avl_struct *node_key = RT_NULL;
    struct lwp_shm_struct *p = RT_NULL;
    void *va = shm_vaddr;

    /* The id is used to locate the node_key in the binary tree, and then get the
     * shared-memory structure linked to the node_key. We don't use the id to refer
     * to the shared-memory structure directly, because the binary tree is used
     * to verify the structure is really in use.
     */
    node_key = shm_id_to_node(id);
    if (!node_key)
    {
        return RT_NULL;
    }
    p = (struct lwp_shm_struct *)node_key->data; /* p = _shm_ary[id]; */

    /* map the shared memory into the address space of the current thread */
    lwp = lwp_self();
    if (!lwp)
    {
        return RT_NULL;
    }

    err = rt_aspace_map(lwp->aspace, &va, p->size, MMU_MAP_U_RWCB, MMF_PREFETCH,
                        &p->mem_obj, 0);
    if (err != RT_EOK)
    {
        va = RT_NULL;
    }
    return va;
}

/* A wrapping function: attach the shared memory to the specified address. */
void *lwp_shmat(int id, void *shm_vaddr)
{
    void *ret = RT_NULL;

    if (((size_t)shm_vaddr & ARCH_PAGE_MASK) != 0)
    {
        return RT_NULL;
    }

    ret = _lwp_shmat(id, shm_vaddr);

    return ret;
}

static struct lwp_shm_struct *_lwp_shm_struct_get(struct rt_lwp *lwp, void *shm_vaddr)
{
    void *pa = RT_NULL;
    struct lwp_avl_struct *node_pa = RT_NULL;

    if (!lwp)
    {
        return RT_NULL;
    }
    pa = lwp_v2p(lwp, shm_vaddr);  /* physical memory */

    node_pa = lwp_avl_find((size_t)pa, shm_tree_pa);
    if (!node_pa)
    {
        return RT_NULL;
    }
    return (struct lwp_shm_struct *)node_pa->data;
}

static int _lwp_shm_ref_inc(struct rt_lwp *lwp, void *shm_vaddr)
{
    struct lwp_shm_struct* p = _lwp_shm_struct_get(lwp, shm_vaddr);

    if (p)
    {
        p->ref++;
        return p->ref;
    }
    return -1;
}

int lwp_shm_ref_inc(struct rt_lwp *lwp, void *shm_vaddr)
{
    int ret = 0;

    rt_mm_lock();
    ret = _lwp_shm_ref_inc(lwp, shm_vaddr);
    rt_mm_unlock();

    return ret;
}

static int _lwp_shm_ref_dec(struct rt_lwp *lwp, void *shm_vaddr)
{
    struct lwp_shm_struct* p = _lwp_shm_struct_get(lwp, shm_vaddr);

    if (p && (p->ref > 0))
    {
        p->ref--;
        return p->ref;
    }
    return -1;
}

int lwp_shm_ref_dec(struct rt_lwp *lwp, void *shm_vaddr)
{
    int ret = 0;

    rt_mm_lock();
    ret = _lwp_shm_ref_dec(lwp, shm_vaddr);
    rt_mm_unlock();

    return ret;
}

/* Unmap the shared memory from the address space of the current thread. */
int _lwp_shmdt(void *shm_vaddr)
{
    struct rt_lwp *lwp = RT_NULL;
    int ret = 0;

    lwp = lwp_self();
    if (!lwp)
    {
        return -1;
    }

    ret = rt_aspace_unmap(lwp->aspace, shm_vaddr);
    if (ret != RT_EOK)
    {
        ret = -1;
    }
    return ret;
}

/* A wrapping function: detach the mapped shared memory. */
int lwp_shmdt(void *shm_vaddr)
{
    int ret = 0;

    rt_mm_lock();
    ret = _lwp_shmdt(shm_vaddr);
    rt_mm_unlock();

    return ret;
}

/* Get the virtual address of a shared memory in kernel. */
void *_lwp_shminfo(int id)
{
    struct lwp_avl_struct *node_key = RT_NULL;
    struct lwp_shm_struct *p = RT_NULL;

    /* the share memory is in use only if it exsits in the binary tree */
    node_key = shm_id_to_node(id);
    if (!node_key)
    {
        return RT_NULL;
    }
    p = (struct lwp_shm_struct *)node_key->data; /* p = _shm_ary[id]; */

    return (void *)((char *)p->addr - PV_OFFSET);     /* get the virtual address */
}

/* A wrapping function: get the virtual address of a shared memory. */
void *lwp_shminfo(int id)
{
    void *vaddr = RT_NULL;

    rt_mm_lock();
    vaddr = _lwp_shminfo(id);
    rt_mm_unlock();
    return vaddr;
}

#ifdef RT_USING_FINSH
static int _shm_info(struct lwp_avl_struct* node_key, void *data)
{
    int id = 0;
    struct lwp_shm_struct* p = (struct lwp_shm_struct *)node_key->data;

    id = p - _shm_ary;
    rt_kprintf("0x%08x 0x%08x 0x%08x %8d\n", p->key, p->addr, p->size, id);
    return 0;
}

void list_shm(void)
{
    rt_kprintf("   key        paddr      size       id\n");
    rt_kprintf("---------- ---------- ---------- --------\n");
    rt_mm_lock();
    lwp_avl_traversal(shm_tree_key, _shm_info, NULL);
    rt_mm_unlock();
}
MSH_CMD_EXPORT(list_shm, show share memory info);
#endif

#endif
