/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdlib.h>
#include <string.h>
#include "pico/util/queue.h"

void queue_init_with_spinlock(queue_t *q, uint element_size, uint element_count, uint spinlock_num) {
    q->lock = spin_lock_instance(spinlock_num);
    q->data = (uint8_t *)calloc(element_count + 1, element_size);
    q->element_count = element_count;
    q->element_size = element_size;
    q->wptr = 0;
    q->rptr = 0;
}

void queue_free(queue_t *q) {
    free(q->data);
}

static inline void *element_ptr(queue_t *q, uint index) {
    assert(index <= q->element_count);
    return q->data + index * q->element_size;
}

static inline uint16_t inc_index(queue_t *q, uint16_t index) {
    if (++index > q->element_count) { // > because we have element_count + 1 elements
        index = 0;
    }
    return index;
}

bool queue_try_add(queue_t *q, void *data) {
    bool success = false;
    uint32_t flags = spin_lock_blocking(q->lock);
    if (queue_get_level_unsafe(q) != q->element_count) {
        memcpy(element_ptr(q, q->wptr), data, q->element_size);
        q->wptr = inc_index(q, q->wptr);
        success = true;
    }
    spin_unlock(q->lock, flags);
    if (success) __sev();
    return success;
}

bool queue_try_remove(queue_t *q, void *data) {
    bool success = false;
    uint32_t flags = spin_lock_blocking(q->lock);
    if (queue_get_level_unsafe(q) != 0) {
        memcpy(data, element_ptr(q, q->rptr), q->element_size);
        q->rptr = inc_index(q, q->rptr);
        success = true;
    }
    spin_unlock(q->lock, flags);
    if (success) __sev();
    return success;
}

bool queue_try_peek(queue_t *q, void *data) {
    bool success = false;
    uint32_t flags = spin_lock_blocking(q->lock);
    if (queue_get_level_unsafe(q) != 0) {
        memcpy(data, element_ptr(q, q->rptr), q->element_size);
        success = true;
    }
    spin_unlock(q->lock, flags);
    return success;
}

void queue_add_blocking(queue_t *q, void *data) {
    bool done;
    do {
        done = queue_try_add(q, data);
        if (done) break;
        __wfe();
    } while (true);
}

void queue_remove_blocking(queue_t *q, void *data) {
    bool done;
    do {
        done = queue_try_remove(q, data);
        if (done) break;
        __wfe();
    } while (true);
}

void queue_peek_blocking(queue_t *q, void *data) {
    bool done;
    do {
        done = queue_try_peek(q, data);
        if (done) break;
        __wfe();
    } while (true);
}
