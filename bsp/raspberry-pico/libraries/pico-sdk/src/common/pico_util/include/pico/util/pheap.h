/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PICO_UTIL_PHEAP_H
#define _PICO_UTIL_PHEAP_H

#include "pico.h"

#ifdef __cplusplus
extern "C" {
#endif

// PICO_CONFIG: PARAM_ASSERTIONS_ENABLED_PHEAP, Enable/disable assertions in the pheap module, type=bool, default=0, group=pico_util
#ifndef PARAM_ASSERTIONS_ENABLED_PHEAP
#define PARAM_ASSERTIONS_ENABLED_PHEAP 0
#endif

/**
 * \file pheap.h
 * \defgroup util_pheap pheap
 * Pairing Heap Implementation
 * \ingroup pico_util
 *
 * pheap defines a simple pairing heap. the implementation simply tracks array indexes, it is up to
 * the user to provide storage for heap entries and a comparison function.
 *
 * NOTE: this class is not safe for concurrent usage. It should be externally protected. Furthermore
 * if used concurrently, the caller needs to protect around their use of the returned id.
 * for example, ph_remove_head returns the id of an element that is no longer in the heap.
 *
 * The user can still use this to look at the data in their companion array, however obviously further operations
 * on the heap may cause them to overwrite that data as the id may be reused on subsequent operations
 *
 */
// PICO_CONFIG: PICO_PHEAP_MAX_ENTRIES, Maximum number of entries in the pheap, min=1, max=65534, default=255, group=pico_util
#ifndef PICO_PHEAP_MAX_ENTRIES
#define PICO_PHEAP_MAX_ENTRIES 255
#endif

// public heap_node ids are numbered from 1 (0 means none)
#if PICO_PHEAP_MAX_ENTRIES < 256
typedef uint8_t pheap_node_id_t;
#elif PICO_PHEAP_MAX_ENTRIES < 65535
typedef uint16_t pheap_node_id_t;
#else
#error invalid PICO_PHEAP_MAX_ENTRIES
#endif

typedef struct pheap_node {
    pheap_node_id_t child, sibling, parent;
} pheap_node_t;

// return true if a < b in natural order
typedef bool (*pheap_comparator)(void *user_data, pheap_node_id_t a, pheap_node_id_t b);

typedef struct pheap {
    pheap_node_t *nodes;
    pheap_comparator comparator;
    void *user_data;
    pheap_node_id_t max_nodes;
    pheap_node_id_t root_id;
    // we remove from head and add to tail to stop reusing the same ids
    pheap_node_id_t free_head_id;
    pheap_node_id_t free_tail_id;
} pheap_t;

pheap_t *ph_create(uint max_nodes, pheap_comparator comparator, void *user_data);

void ph_clear(pheap_t *heap);

void ph_destroy(pheap_t *heap);

static inline pheap_node_t *ph_get_node(pheap_t *heap, pheap_node_id_t id) {
    assert(id && id <= heap->max_nodes);
    return heap->nodes + id - 1;
}

static void ph_add_child_node(pheap_t *heap, pheap_node_id_t parent_id, pheap_node_id_t child_id) {
    pheap_node_t *n = ph_get_node(heap, parent_id);
    assert(parent_id);
    assert(child_id);
    assert(parent_id != child_id);
    pheap_node_t *c = ph_get_node(heap, child_id);
    c->parent = parent_id;
    if (!n->child) {
        n->child = child_id;
    } else {
        c->sibling = n->child;
        n->child = child_id;
    }
}

static pheap_node_id_t ph_merge_nodes(pheap_t *heap, pheap_node_id_t a, pheap_node_id_t b) {
    if (!a) return b;
    if (!b) return a;
    if (heap->comparator(heap->user_data, a, b)) {
        ph_add_child_node(heap, a, b);
        return a;
    } else {
        ph_add_child_node(heap, b, a);
        return b;
    }
}

static inline pheap_node_id_t ph_new_node(pheap_t *heap) {
    if (!heap->free_head_id) return 0;
    pheap_node_id_t id = heap->free_head_id;
    heap->free_head_id = ph_get_node(heap, id)->sibling;
    if (!heap->free_head_id) heap->free_tail_id = 0;
    return id;
}

// note this will callback the comparator for the node
// returns the (new) root of the heap
static inline pheap_node_id_t ph_insert(pheap_t *heap, pheap_node_id_t id) {
    assert(id);
    pheap_node_t *hn = ph_get_node(heap, id);
    hn->child = hn->sibling = hn->parent = 0;
    heap->root_id = ph_merge_nodes(heap, heap->root_id, id);
    return heap->root_id;
}

static inline pheap_node_id_t ph_peek_head(pheap_t *heap) {
    return heap->root_id;
}

pheap_node_id_t ph_remove_head_reserve(pheap_t *heap, bool reserve);

static inline pheap_node_id_t ph_remove_head(pheap_t *heap) {
    return ph_remove_head_reserve(heap, false);
}

static inline bool ph_contains(pheap_t *heap, pheap_node_id_t id) {
    return id == heap->root_id || ph_get_node(heap, id)->parent;
}

bool ph_delete(pheap_t *heap, pheap_node_id_t id);

static inline void ph_add_to_free_list(pheap_t *heap, pheap_node_id_t id) {
    assert(id && !ph_contains(heap, id));
    if (heap->free_tail_id) {
        ph_get_node(heap, heap->free_tail_id)->sibling = id;
    }
    heap->free_tail_id = id;
}

void ph_dump(pheap_t *heap, void (*dump_key)(pheap_node_id_t, void *), void *user_data);
#ifdef __cplusplus
}
#endif

#endif
