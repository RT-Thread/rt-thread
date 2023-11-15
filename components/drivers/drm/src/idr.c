#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include "inc/idr.h"

struct id_node {
    unsigned long id;
    void* ptr;
    struct avl_node avl;
};

static int idr_key_node_comp(void* key, struct avl_node* node)
{
    struct id_node* r1 = (struct id_node*)key;
    struct id_node* r2 = avl_entry(node, struct id_node, avl);

    if (r1->id < r2->id)
        return -1;
    else if (r1->id > r2->id)
        return 1;
    return 0;
}

static int idr_node_node_comp(struct avl_node* node1, struct avl_node* node2)
{
    struct id_node* r1 = avl_entry(node1, struct id_node, avl);
    struct id_node* r2 = avl_entry(node2, struct id_node, avl);

    if (r1->id < r2->id)
        return -1;
    else if (r1->id > r2->id)
        return 1;
    return 0;
}

void idr_avl_start_iter(struct avl_root* root, struct avl_iter* iter, void* key,
                        int flags)
{
    avl_start_iter(root, iter, key, flags);
}

static struct id_node* idr_avl_get_iter(struct avl_iter* iter)
{
    struct avl_node* node = avl_get_iter(iter);
    if (!node) return NULL;
    return avl_entry(node, struct id_node, avl);
}

void idr_init_base(struct idr* idr, unsigned int base)
{
    INIT_AVL_ROOT(&idr->root, idr_key_node_comp, idr_node_node_comp);
    idr->base = base;
    idr->next = 0;
}

void idr_init_new(struct idr* idr) { idr_init_base(idr, 0); }

int idr_alloc_new(struct idr* idr, void* ptr, int start, int end)
{
    rt_uint32_t id = start;
    int ret;

    if (start < 0) return -EINVAL;

    ret = idr_alloc_u32(idr, ptr, &id, end > 0 ? end - 1 : INT_MAX);
    if (ret) return ret;

    return id;
}

int idr_alloc_u32(struct idr* idr, void* ptr, rt_uint32_t* nextid, unsigned long max)
{
    struct avl_iter iter;
    struct id_node id_max, *last, *node, *prev_node;
    unsigned int slot;
    unsigned int base = idr->base;
    unsigned int id = *nextid;
    int found = 0;

    id = (id < base) ? 0 : (id - base);
    id_max.id = max - base;

    idr_avl_start_iter(&idr->root, &iter, &id_max, AVL_GREATER_EQUAL);
    last = idr_avl_get_iter(&iter);

    if (!last) {
        idr_avl_start_iter(&idr->root, &iter, &id_max, AVL_LESS);
        last = idr_avl_get_iter(&iter);

        if (!last) {
            /* idr is empty so just use the first one */
            slot = id;
            found = 1;
        } else {
            slot = last->id + 1;
            found = 1;
        }
    } else {
        while ((node = idr_avl_get_iter(&iter)) && !found) {
            avl_dec_iter(&iter);
            prev_node = idr_avl_get_iter(&iter);
            slot = prev_node->id + 1;

            if (slot < node->id && slot >= id) {
                found = 1;
            }
        }
    }

    if (!found) return -ENOSPC;

    node = malloc(sizeof(*node));
    if (!node) return -ENOMEM;

    node->id = slot;
    node->ptr = ptr;
    avl_insert(&node->avl, &idr->root);

    *nextid = base + slot;

    return 0;
}

void* idr_remove_new(struct idr* idr, unsigned long id)
{
    struct avl_node* node = idr->root.node;
    struct id_node* id_node;
    void* ptr;

    if (id < idr->base) return NULL;
    id -= idr->base;

    while (node) {
        id_node = avl_entry(node, struct id_node, avl);

        if (id == id_node->id) {
            ptr = id_node->ptr;
            avl_erase(node, &idr->root);
            free(id_node);

            return ptr;
        } else if (id < id_node->id) {
            node = node->left;
        } else if (id > id_node->id) {
            node = node->right;
        }
    }

    return NULL;
}

void* idr_find_new(const struct idr* idr, unsigned long id)
{
    struct avl_node* node = idr->root.node;
    struct id_node* id_node;

    if (id < idr->base) return NULL;
    id -= idr->base;

    while (node) {
        id_node = avl_entry(node, struct id_node, avl);

        if (id == id_node->id) {
            return id_node->ptr;
        } else if (id < id_node->id) {
            node = node->left;
        } else if (id > id_node->id) {
            node = node->right;
        }
    }

    return NULL;
}

void idr_destroy(struct idr* idr) {}
