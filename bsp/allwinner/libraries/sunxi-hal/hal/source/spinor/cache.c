#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <hal_timer.h>

#include "inter.h"

#define addr_to_blk(nor, addr) ((addr) / nor->blk_size)
#define addr_to_page(nor, addr) ((addr) / nor->page_size)

typedef struct {
#define CACHE_SIZE SZ_64K
    char *buf;
#define INVALID_CACHE_ADDR ((unsigned int)-1)
    unsigned int addr;
} cache_t;

struct nor_cache {
    cache_t cache;
    unsigned int last_write;

    unsigned long *bitmap_page;
    unsigned int page_cnt;
    unsigned long *bitmap_blk;
    unsigned int blk_cnt;

    struct nor_flash *nor;
};
static struct nor_cache g_nor_cache;

hal_sem_t lock_nor_cache;

static inline int nor_lock_init(void)
{
    lock_nor_cache = hal_sem_create(1);
    if (!lock_nor_cache) {
        SPINOR_ERR("create hal_sem lock for nor_flash failed\n");
        return -1;
    }
    return 0;
}

static int nor_cache_lock(void)
{
    return hal_sem_wait(lock_nor_cache);
}

static int nor_cache_trylock(void)
{
    return hal_sem_trywait(lock_nor_cache);
}

static int nor_cache_unlock(void)
{
    return hal_sem_post(lock_nor_cache);
}

static void clear_cache(cache_t *c)
{
    SPINOR_DEBUG("clear cache addr 0x%x\n", c->addr);
    memset(c->buf, 0xFF, CACHE_SIZE);
    c->addr = INVALID_CACHE_ADDR;
}

static void delete_cache(cache_t *c)
{
    free(c->buf);
    c->buf = NULL;
    c->addr = 0;
}

static int init_cache(cache_t *c)
{
    c->buf = malloc(CACHE_SIZE);
    if (!c->buf)
        return -ENOMEM;

    clear_cache(c);
    return 0;
}

static int init_bitmap(struct nor_cache *nc)
{
    struct nor_flash *nor = nc->nor;

    nc->page_cnt = CACHE_SIZE / nor->page_size;
    nc->bitmap_page = malloc(BITS_TO_LONGS(nc->page_cnt) * sizeof(long));
    if (!nc->bitmap_page)
        return -ENOMEM;
    memset(nc->bitmap_page, 0, BITS_TO_LONGS(nc->page_cnt) * sizeof(long));

    nc->blk_cnt = CACHE_SIZE / nor->blk_size;
    nc->bitmap_blk = malloc(BITS_TO_LONGS(nc->blk_cnt) * sizeof(long));
    if (!nc->blk_cnt)
        goto free_page;
    memset(nc->bitmap_blk, 0, BITS_TO_LONGS(nc->blk_cnt) * sizeof(long));

    return 0;
free_page:
    free(nc->bitmap_page);
    return -ENOMEM;
}

static void delete_bitmap(struct nor_cache *nc)
{
    free(nc->bitmap_blk);
    nc->bitmap_blk = NULL;

    free(nc->bitmap_page);
    nc->bitmap_page = NULL;
}

int nor_cache_init(struct nor_flash *nor)
{
    int ret = -ENOMEM;
    struct nor_cache *nc = &g_nor_cache;

    /* initialized before */
    if (nc->cache.buf)
        return -EBUSY;

    ret = nor_lock_init();
    if (ret)
        return ret;

    nor_cache_lock();

    ret = init_cache(&nc->cache);
    if (ret)
        goto unlock;

    nc->nor = nor;
    ret = init_bitmap(nc);
    if (ret)
        goto free_cache;

    nor_cache_unlock();
    return 0;

/*
 * free_bitmap:
 *     delete_bitmap(nc);
 */
free_cache:
    delete_cache(&nc->cache);
unlock:
    nor_cache_unlock();
    return ret;
}

void nor_cache_exit(void)
{
    struct nor_cache *nc = &g_nor_cache;

    delete_cache(&nc->cache);
    delete_bitmap(nc);
}

static int check_cache_addr(cache_t *c, unsigned int addr, unsigned int len)
{
    if (c->addr == INVALID_CACHE_ADDR)
        return -1;
    /* start boundary */
    if (ALIGN_DOWN(addr, CACHE_SIZE) != c->addr)
        return -1;
    /* end boundary */
    if (ALIGN_DOWN(addr + len - 1, CACHE_SIZE) != c->addr)
        return -1;
    return 0;
}

static inline void set_cache_addr(cache_t *c, unsigned int addr)
{
    c->addr = ALIGN_DOWN(addr, CACHE_SIZE);
    SPINOR_DEBUG("set cache addr as 0x%x\n", c->addr);
}

static inline unsigned int get_addr_by_page(unsigned int page)
{
    struct nor_cache *nc = &g_nor_cache;
    struct nor_flash *nor = nc->nor;
    cache_t *c = &nc->cache;

    return c->addr + page * nor->page_size;
}

static inline unsigned int get_addr_by_blk(unsigned int blk)
{
    struct nor_cache *nc = &g_nor_cache;
    struct nor_flash *nor = nc->nor;
    cache_t *c = &nc->cache;

    return c->addr + blk * nor->blk_size;
}

static inline void set_bit(int nr, unsigned long *addr)
{
    addr[nr / BITS_PER_LONG] |= 1UL << (nr % BITS_PER_LONG);
}

static __always_inline int test_bit(unsigned int nr, const unsigned long *addr)
{
    return ((1UL << (nr % BITS_PER_LONG)) &
            (((unsigned long *)addr)[nr / BITS_PER_LONG])) != 0;
}

static int nor_flush_erase(struct nor_cache *nc)
{
    struct nor_flash *nor = nc->nor;
    unsigned int start, end;
    int ret;

    for (end = start = 0; end < nc->blk_cnt; end++) {
        /* we should do erase lazy to get more continuous erase block */
        if (test_bit(end, nc->bitmap_blk))
            continue;
        /* continuous zero, do nothing */
        if (start == end) {
            start = end + 1;
            continue;
        }

        SPINOR_DEBUG("flush erase: addr 0x%x blk cnt %u\n",
                get_addr_by_blk(start), end - start);
        ret = nor_erase(get_addr_by_blk(start), (end - start) * nor->blk_size);
        if (ret)
            return ret;

        start = end + 1;
    }

    if (start != end) {
        SPINOR_DEBUG("flush erase: addr 0x%x blk cnt %u\n",
                get_addr_by_blk(start), end - start);
        ret = nor_erase(get_addr_by_blk(start), (end - start) * nor->blk_size);
        if (ret)
            return ret;
    }

    memset(nc->bitmap_blk, 0, BITS_TO_LONGS(nc->blk_cnt) * sizeof(long));
    return 0;
}

static int nor_flush_write(struct nor_cache *nc)
{
    struct nor_flash *nor = nc->nor;
    cache_t *c = &nc->cache;
    unsigned int page, i;
    char *buf = c->buf;
    int ret;

    for (i = 0; i < nc->page_cnt; i++) {
        /* let start with (last_write page + 1) */
        page = (i + nc->last_write + 1) % nc->page_cnt;

        if (!test_bit(page, nc->bitmap_page))
            continue;

        SPINOR_DEBUG("flush write: addr 0x%x\n", get_addr_by_page(page));
        ret = nor_write(get_addr_by_page(page),
                buf + page * nor->page_size, nor->page_size);
        if (ret)
            return ret;
    }

    memset(nc->bitmap_page, 0, BITS_TO_LONGS(nc->page_cnt) * sizeof(long));
    return 0;
}

static int nor_flush_cache(struct nor_cache *nc)
{
    int ret;

    if (nc->cache.addr == INVALID_CACHE_ADDR)
        return 0;

    ret = nor_flush_erase(nc);
    if (ret)
        return ret;

    ret = nor_flush_write(nc);
    if (ret)
        return ret;

    clear_cache(&nc->cache);
    return 0;
}

int nor_cache_write(unsigned int addr, char *buf, unsigned int len)
{
    struct nor_cache *nc = &g_nor_cache;
    struct nor_flash *nor = nc->nor;
    cache_t *c = &nc->cache;
    char *pbuf;
    unsigned int page;
    int ret;

    SPINOR_DEBUG("try to write addr 0x%x with size %u\n", addr, len);

    if (addr % nor->page_size) {
        SPINOR_ERR("addr %u must align to page size %u\n", addr, nor->page_size);
        return -EINVAL;
    }

    if (len % nor->page_size) {
        SPINOR_ERR("len %u must align to page size %u\n", len, nor->page_size);
        return -EINVAL;
    }

    ret = nor_cache_lock();
    if (ret)
        return ret;

    /* if over CACHE_SIZE, write roughly */
    if (len > CACHE_SIZE ||
            (addr - ALIGN_DOWN(addr, CACHE_SIZE) + len > CACHE_SIZE)) {
        ret = nor_flush_cache(nc);
        if (ret)
            goto unlock;

        ret = nor_write(addr, buf, len);
        goto unlock;
    }

    ret = check_cache_addr(c, addr, len);
    if (ret) {
        SPINOR_DEBUG("write addr 0x%x len %d over cache addr 0x%x\n",
                addr, len, c->addr);

        /* if write to a new addr out of cache, just flush cache for new one */
        ret = nor_flush_cache(nc);
        if (ret)
            goto unlock;

        /* ready new cache for data */
        set_cache_addr(c, addr);
    }

    pbuf = c->buf + (addr - c->addr);
    page = addr_to_page(nor, addr - c->addr);
    while (len) {
        unsigned int size = min(len, nor->page_size);

        memcpy(pbuf, buf, size);

        SPINOR_DEBUG("write: mark page %d abs addr 0x%x\n", page,
                get_addr_by_page(page));
        set_bit(page, nc->bitmap_page);

        /*
         * The order of page to flush-write is very pivotal. On lfs,
         * the last page before sync always meta data. We must ensure normal
         * data to write to flash before meta data. So, we must save the
         * last page and flush this page at last.
         */
        nc->last_write = page;

        page += 1;
        pbuf += size;
        buf += size;
        len -= size;
    }

    ret = 0;
unlock:
    nor_cache_unlock();
    return ret;
}

int nor_cache_read(unsigned int addr, char *buf, unsigned int len)
{
    struct nor_cache *nc = &g_nor_cache;
    struct nor_flash *nor = nc->nor;
    cache_t *c = &nc->cache;
    char *pbuf;
    unsigned int page, blk;
    int ret;

    SPINOR_DEBUG("try to read addr 0x%x with size %u\n", addr, len);

    if (addr % nor->page_size) {
        SPINOR_ERR("addr %u must align to page size %u\n", addr, nor->page_size);
        return -EINVAL;
    }

    if (len % nor->page_size) {
        SPINOR_ERR("len %u must align to page size %u\n", len, nor->page_size);
        return -EINVAL;
    }

    ret = nor_cache_lock();
    if (ret)
        return ret;

    /* if over CACHE_SIZE, write roughly */
    if (len > CACHE_SIZE ||
            (addr - ALIGN_DOWN(addr, CACHE_SIZE) + len > CACHE_SIZE)) {
        ret = nor_flush_cache(nc);
        if (ret)
            goto unlock;

        ret = nor_read(addr, buf, len);
        goto unlock;
    }

    ret = check_cache_addr(c, addr, len);
    if (ret) {
        ret = nor_read(addr, buf, len);
        goto unlock;
    }

    pbuf = c->buf + (addr - c->addr);
    page = addr_to_page(nor, addr - c->addr);
    while (len) {
        unsigned int size = min(len, nor->page_size);

        if (test_bit(page, nc->bitmap_page)) {
            SPINOR_DEBUG("read match cache page %d addr 0x%x\n", page,
                    get_addr_by_page(page));
            memcpy(buf, pbuf, size);
        } else {
            blk = addr_to_blk(nor, addr - c->addr);
            if (test_bit(blk, nc->bitmap_blk)) {
                SPINOR_DEBUG("read match cache erase blk 0x%x addr 0x%x\n",
                                             blk, get_addr_by_page(page));
                memset(buf, 0xFF, size);
            } else {
                SPINOR_DEBUG("read not match cache addr 0x%x\n",
                                             get_addr_by_page(page));
                ret = nor_read(get_addr_by_page(page), buf, size);
                if (ret)
                    goto unlock;
            }
        }

        page += 1;
        pbuf += size;
        buf += size;
        len -= size;
    }

    ret = 0;
unlock:
    nor_cache_unlock();
    return ret;
}

int nor_cache_sync(void)
{
    struct nor_cache *nc = &g_nor_cache;
    int ret;

    SPINOR_DEBUG("try to sync nor cache\n");
    ret = nor_cache_trylock();
    if (ret) {
        SPINOR_DEBUG("trylock fail, skip sync nor cache\n");
        return ret;
    }

    ret = nor_flush_cache(nc);

    nor_cache_unlock();

    return ret? -1 : 0;
}

int nor_cache_erase(unsigned int addr, unsigned int len)
{
    struct nor_cache *nc = &g_nor_cache;
    struct nor_flash *nor = nc->nor;
    cache_t *c = &nc->cache;
    unsigned int blk;
    int ret;

    SPINOR_DEBUG("try to erase addr 0x%x with size %u\n", addr, len);

    if (addr % nor->blk_size) {
        SPINOR_ERR("addr %u must align to blk size %u\n", addr, nor->blk_size);
        return -EINVAL;
    }

    if (len % nor->blk_size) {
        SPINOR_ERR("len %u must align to blk size %u\n", len, nor->blk_size);
        return -EINVAL;
    }

    ret = nor_cache_lock();
    if (ret)
        return ret;

    /* if over CACHE_SIZE, erase roughly */
    if (len > CACHE_SIZE ||
            (addr - ALIGN_DOWN(addr, CACHE_SIZE) + len > CACHE_SIZE)) {
        /* just flush earse operation */
        ret = nor_flush_erase(nc);
        if (ret)
            goto unlock;

        ret = nor_erase(addr, len);
        goto unlock;
    }

    ret = check_cache_addr(c, addr, len);
    if (ret) {
        SPINOR_DEBUG("erase addr 0x%x len %d over cache addr 0x%x\n",
                addr, len, c->addr);

        /* if erase to a new addr out of cache, just flush cache for new one */
        ret = nor_flush_cache(nc);
        if (ret)
            goto unlock;

        /* ready new cache for data */
        set_cache_addr(c, addr);
    }

    blk = addr_to_blk(nor, addr - c->addr);
    for (; len; len -= nor->blk_size, blk++) {
        SPINOR_DEBUG("erase: mark blk %d addr 0x%x\n", blk, get_addr_by_blk(blk));
        set_bit(blk, nc->bitmap_blk);
    }

    ret = 0;
unlock:
    nor_cache_unlock();
    return ret;
}
