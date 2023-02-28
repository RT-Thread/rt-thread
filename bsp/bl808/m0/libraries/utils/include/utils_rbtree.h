/*
 * Copyright (c) 2016-2022 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __UTILS_RBTREE_H__
#define __UTILS_RBTREE_H__

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

#ifndef RB_ITER_MAX_HEIGHT
#define RB_ITER_MAX_HEIGHT 64 // Tallest allowable tree to iterate
#endif

struct rb_node;
struct rb_tree;

typedef int  (*rb_tree_node_cmp_f) (struct rb_tree *self, struct rb_node *a, struct rb_node *b);
typedef void (*rb_tree_node_f)     (struct rb_tree *self, struct rb_node *node);

struct rb_node {
    int             red;     // Color red (1), black (0)
    struct rb_node *link[2]; // Link left [0] and right [1]
    void           *value;   // User provided, used indirectly via rb_tree_node_cmp_f.
};

struct rb_tree {
    struct rb_node    *root;
    rb_tree_node_cmp_f cmp;
    size_t             size;
    void              *info; // User provided, not used by rb_tree.
};

struct rb_iter {
    struct rb_tree *tree;
    struct rb_node *node;                     // Current node
    struct rb_node *path[RB_ITER_MAX_HEIGHT]; // Traversal path
    size_t          top;                      // Top of stack
    void           *info;                     // User provided, not used by rb_iter.
};

int             rb_tree_node_cmp_ptr_cb (struct rb_tree *self, struct rb_node *a, struct rb_node *b);
void            rb_tree_node_dealloc_cb (struct rb_tree *self, struct rb_node *node);

struct rb_node *rb_node_alloc           ();
struct rb_node *rb_node_create          (void *value);
struct rb_node *rb_node_init            (struct rb_node *self, void *value);
void            rb_node_dealloc         (struct rb_node *self);

struct rb_tree *rb_tree_alloc           ();
struct rb_tree *rb_tree_create          (rb_tree_node_cmp_f cmp);
struct rb_tree *rb_tree_init            (struct rb_tree *self, rb_tree_node_cmp_f cmp);
void            rb_tree_dealloc         (struct rb_tree *self, rb_tree_node_f node_cb);
void           *rb_tree_find            (struct rb_tree *self, void *value);
int             rb_tree_insert          (struct rb_tree *self, void *value);
int             rb_tree_remove          (struct rb_tree *self, void *value);
size_t          rb_tree_size            (struct rb_tree *self);

int             rb_tree_insert_node     (struct rb_tree *self, struct rb_node *node);
int             rb_tree_remove_with_cb  (struct rb_tree *self, void *value, rb_tree_node_f node_cb);

int             rb_tree_test            (struct rb_tree *self, struct rb_node *root);

struct rb_iter *rb_iter_alloc           ();
struct rb_iter *rb_iter_init            ();
struct rb_iter *rb_iter_create          ();
void            rb_iter_dealloc         (struct rb_iter *self);
void           *rb_iter_first           (struct rb_iter *self, struct rb_tree *tree);
void           *rb_iter_last            (struct rb_iter *self, struct rb_tree *tree);
void           *rb_iter_next            (struct rb_iter *self);
void           *rb_iter_prev            (struct rb_iter *self);

#endif
