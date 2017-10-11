/*
 * File      : image_container.c
 * This file is part of RT-Thread GUI Engine
 * COPYRIGHT (C) 2006 - 2017, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-09-15     Bernard      first version
 */
#include <rtgui/rtgui_system.h>
#include <rtgui/image_container.h>

/*
 * ImageContainer is a Image pool to manage image resource in the system.
 *
 * All of image in the ImageContainer should be loaded in the memory.
 * All of image are identified by image file name.
 *
 * Applications can use rtgui_image_container_get/put to refer or derefer
 * a image resource.
 */

#if defined(RTGUI_IMAGE_CONTAINER) && defined(RTGUI_USING_DFS_FILERW)
typedef unsigned int (*rtgui_hash_func_t)(const void *key);
typedef struct _rtgui_hash_table  rtgui_hash_table_t;
typedef rt_bool_t (*rtgui_equal_func_t)(const void *a, const void *b);
typedef void (*rtgui_user_func_t)(const void *value, const void *data);

/*
 *Hash tables
 */
rtgui_hash_table_t *hash_table_create(rtgui_hash_func_t hash_func, rtgui_equal_func_t key_equal_func);
void hash_table_destroy(rtgui_hash_table_t *hash_table);

void *hash_table_find(rtgui_hash_table_t *hash_table, const void *key);
void hash_table_insert(rtgui_hash_table_t *hash_table, const void *key, void *value);
rt_bool_t hash_table_remove(rtgui_hash_table_t *hash_table, const void *key);

void hash_table_foreach(rtgui_hash_table_t *hash_table, rtgui_user_func_t user_func, void *data);
unsigned int hash_table_get_size(rtgui_hash_table_t *hash_table);

/* Hash Functions
 */
unsigned int direct_hash(const void *v);

#define HASH_TABLE_MIN_SIZE 11
#define HASH_TABLE_MAX_SIZE 6247

typedef struct _gui_hash_node rtgui_hash_node_t;
struct _gui_hash_node
{
    const void *key;
    void *value;
    rtgui_hash_node_t *next;
};

struct _rtgui_hash_table
{
    rt_uint16_t size;
    rt_uint16_t nnodes;

    rtgui_hash_node_t **nodes;
    rtgui_hash_func_t hash_func;
    rtgui_equal_func_t key_equal_func;
};

static const unsigned int primes[] =
{
    11,
    19,
    37,
    73,
    109,
    163,
    251,
    367,
    557,
    823,
    1237,
    1861,
    2777,
    4177,
    6247,
};

static const unsigned int nprimes = sizeof(primes) / sizeof(primes[0]);

static void hash_table_resize(rtgui_hash_table_t *hash_table);
static rtgui_hash_node_t **hash_table_find_node(rtgui_hash_table_t *hash_table, const void *key);
static rtgui_hash_node_t *hash_node_create(const void *key, void *value);
static void hash_node_destroy(rtgui_hash_node_t *hash_node);
static void hash_nodes_destroy(rtgui_hash_node_t *hash_node);
static unsigned int primes_closest(unsigned int num);
static void hash_table_needresize(rtgui_hash_table_t *hash_table);

rt_inline unsigned int primes_closest(unsigned int num)
{
    unsigned int i;

    for (i = 0; i < nprimes; i++)
        if (primes[i] > num)
            return primes[i];

    return primes[nprimes - 1];
}

/* directly hash */
unsigned int direct_hash(const void *v)
{
    return (unsigned int)v;
}

rtgui_hash_table_t *hash_table_create(rtgui_hash_func_t hash_func, rtgui_equal_func_t key_equal_func)
{
    rtgui_hash_table_t *hash_table;

    hash_table = (rtgui_hash_table_t *) rtgui_malloc(sizeof(rtgui_hash_table_t));
    if (hash_table != RT_NULL)
    {
        hash_table->size               = HASH_TABLE_MIN_SIZE;
        hash_table->nnodes             = 0;
        hash_table->hash_func          = hash_func ? hash_func : direct_hash;
        hash_table->key_equal_func     = key_equal_func;
        hash_table->nodes              = (rtgui_hash_node_t **)rtgui_malloc(sizeof(rtgui_hash_node_t *) * hash_table->size);
        if (hash_table->nodes == RT_NULL)
        {
            /* no memory yet */
            rtgui_free(hash_table);
            return RT_NULL;
        }

        rt_memset(hash_table->nodes, 0, sizeof(rtgui_hash_node_t *) * hash_table->size);
    }

    return hash_table;
}

void hash_table_destroy(rtgui_hash_table_t *hash_table)
{
    unsigned int i;

    RT_ASSERT(hash_table != RT_NULL);

    for (i = 0; i < hash_table->size; i++)
        hash_nodes_destroy(hash_table->nodes[i]);

    rtgui_free(hash_table->nodes);
    rtgui_free(hash_table);
}

static rtgui_hash_node_t **hash_table_find_node(rtgui_hash_table_t *hash_table, const void *key)
{
    rtgui_hash_node_t **node;

    node = &hash_table->nodes [(* hash_table->hash_func)(key) % hash_table->size];

    if (hash_table->key_equal_func)
        while (*node && !(*hash_table->key_equal_func)((*node)->key, key))
            node = &(*node)->next;
    else
        while (*node && (*node)->key != key)
            node = &(*node)->next;

    return node;
}

void *hash_table_find(rtgui_hash_table_t *hash_table, const void *key)
{
    rtgui_hash_node_t *node;

    RT_ASSERT(hash_table != RT_NULL);
    RT_ASSERT(key != RT_NULL);

    node = *hash_table_find_node(hash_table, key);

    if (node) return node->value;
    else return RT_NULL;
}

void hash_table_insert(rtgui_hash_table_t *hash_table, const void *key, void *value)
{
    rtgui_hash_node_t **node;

    if (hash_table == RT_NULL)return;

    node = hash_table_find_node(hash_table, key);
    if (*node)
    {
        (*node)->value = value;
    }
    else
    {
        *node = hash_node_create(key, value);
        hash_table->nnodes++;
        hash_table_needresize(hash_table);
    }
}

rt_bool_t hash_table_remove(rtgui_hash_table_t *hash_table, const void  *key)
{
    rtgui_hash_node_t **node, *dest;

    if (hash_table == RT_NULL) return RT_FALSE;

    node = hash_table_find_node(hash_table, key);
    if (*node)
    {
        rt_enter_critical();
        dest = *node;
        (*node) = dest->next;
        hash_node_destroy(dest);
        hash_table->nnodes--;

        hash_table_needresize(hash_table);
        rt_exit_critical();

        return RT_TRUE;
    }

    return RT_FALSE;
}

void hash_table_foreach(rtgui_hash_table_t *hash_table, rtgui_user_func_t user_func, void *data)
{
    rtgui_hash_node_t *node;
    int i;

    RT_ASSERT(hash_table != RT_NULL);
    RT_ASSERT(user_func != RT_NULL);

    for (i = 0; i < hash_table->size; i++)
        for (node = hash_table->nodes[i]; node; node = node->next)
            (* user_func)(node->value, data);
}

unsigned int hash_table_get_size(rtgui_hash_table_t *hash_table)
{
    if (hash_table == NULL) return 0;

    return hash_table->nnodes;
}

static void hash_table_needresize(rtgui_hash_table_t *hash_table)
{
    if ((hash_table->size >= 3 * hash_table->nnodes && hash_table->size > HASH_TABLE_MIN_SIZE) ||
            (3 * hash_table->size <= hash_table->nnodes && hash_table->size < HASH_TABLE_MAX_SIZE))
        hash_table_resize(hash_table);
}

static void hash_table_resize(rtgui_hash_table_t *hash_table)
{
    rtgui_hash_node_t **new_nodes;
    rtgui_hash_node_t *node;
    rtgui_hash_node_t *next;
    unsigned int hash_val;
    int new_size;
    int i;

    i = primes_closest(hash_table->nnodes);
    new_size = i > HASH_TABLE_MAX_SIZE ? HASH_TABLE_MAX_SIZE : i < HASH_TABLE_MIN_SIZE ? HASH_TABLE_MIN_SIZE : i ;

    new_nodes = (rtgui_hash_node_t **)rtgui_malloc(sizeof(rtgui_hash_node_t *) * new_size);
    if (new_nodes == RT_NULL) return; /* no memory yet */
    rt_memset(new_nodes, 0, sizeof(rtgui_hash_node_t *) * new_size);

    for (i = 0; i < hash_table->size; i++)
    {
        for (node = hash_table->nodes[i]; node; node = next)
        {
            next = node->next;

            hash_val = (* hash_table->hash_func)(node->key) % new_size;

            node->next = new_nodes[hash_val];
            new_nodes[hash_val] = node;
        }
    }

    rtgui_free(hash_table->nodes);
    hash_table->nodes = new_nodes;
    hash_table->size = new_size;
}

static rtgui_hash_node_t *hash_node_create(const void *key, void *value)
{
    rtgui_hash_node_t *hash_node;

    hash_node = (rtgui_hash_node_t *) rtgui_malloc(sizeof(rtgui_hash_node_t));
    if (hash_node != RT_NULL)
    {
        /* set value and key */
        hash_node->key = key;
        hash_node->value = value;;

        hash_node->next = RT_NULL;
    }

    return hash_node;
}

static void hash_node_destroy(rtgui_hash_node_t *hash_node)
{
    rtgui_free(hash_node);
}

static void hash_nodes_destroy(rtgui_hash_node_t *hash_node)
{
    if (hash_node)
    {
        rtgui_hash_node_t *node = hash_node;
        rtgui_hash_node_t *temp;

        while (node->next)
        {
            node->key = NULL;
            node->value = NULL;

            temp = node;
            node = node->next;
            rtgui_free(temp);
        }

        node->key = NULL;
        node->value = NULL;
        rtgui_free(node);
    }
}

unsigned int string_hash_func(const void *self)
{
    const char *p;
    int h = 0, g;

    for (p = self; *p != '\0'; p += 1)
    {
        h = (h << 4) + *p;
        g = h;

        if (g & 0xf0000000)
        {
            h = h ^ (g >> 24);
            h = h ^ g;
        }
    }

    return h ;
}

rt_bool_t string_equal_func(const void *a, const void *b)
{
    const char *str1, *str2;

    str1 = (const char *)a;
    str2 = (const char *)b;

    if (strcmp(str1, str2) == 0) return RT_TRUE;
    return RT_FALSE;
}

static rtgui_hash_table_t *image_hash_table;
static struct rt_mutex _image_hash_lock;

void rtgui_system_image_container_init(void)
{
    rt_mutex_init(&_image_hash_lock, "image", RT_IPC_FLAG_FIFO);

    /* create image hash table */
    image_hash_table = hash_table_create(string_hash_func, string_equal_func);
    RT_ASSERT(image_hash_table != RT_NULL);
}

rtgui_image_item_t *rtgui_image_container_get(const char *filename)
{
    struct rtgui_image_item *item = RT_NULL;

    if (rt_mutex_take(&_image_hash_lock, RT_WAITING_FOREVER) == RT_EOK)
    {
        item = hash_table_find(image_hash_table, filename);
        if (item == RT_NULL)
        {
            item = (struct rtgui_image_item *) rtgui_malloc(sizeof(struct rtgui_image_item));
            if (item == RT_NULL) return RT_NULL;

            /* create a image object */
            item->image = rtgui_image_create(filename, RT_TRUE);
            if (item->image == RT_NULL)
            {
                rtgui_free(item);
                return RT_NULL; /* create image failed */
            }
            item->refcount = 1;
            item->filename = rt_strdup(filename);
            hash_table_insert(image_hash_table, item->filename, item);
        }
        else
        {
            item->refcount ++; /* increase refcount */
        }

        rt_mutex_release(&_image_hash_lock);
    }

    return item;
}
RTM_EXPORT(rtgui_image_container_get);

void rtgui_image_container_put(rtgui_image_item_t *item)
{
    rt_mutex_take(&_image_hash_lock, RT_WAITING_FOREVER);
    item->refcount --;
    if (item->refcount == 0)
    {
        /* remove item from container */
        hash_table_remove(image_hash_table, item->filename);

        /* destroy image and image item */
        rt_free(item->filename);
        rtgui_image_destroy(item->image);
        rtgui_free(item);
    }
    rt_mutex_release(&_image_hash_lock);
}
RTM_EXPORT(rtgui_image_container_put);

#endif

