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
#include "../../include/utils_rbtree.h"
#include <stdint.h>
#include <stdio.h>

struct iovec {
    void  *iov_base; // [XSI] Base address of I/O memory region
    size_t iov_len;  // [XSI] Size of region iov_base points to
};

static int my_cmp_cb(struct rb_tree *self, struct rb_node *node_a, struct rb_node *node_b) 
{
    struct iovec *a = (struct iovec *) node_a->value;
    struct iovec *b = (struct iovec *) node_b->value;

    return (a->iov_len > b->iov_len) - (a->iov_len < b->iov_len);
}

int main(int argc, char *argv[])
{
    struct rb_tree *tree = rb_tree_create(my_cmp_cb);
    if (tree) {
        // Use the tree here...
        for (int i = 0; i < 10; i++) {
            struct iovec *v = malloc(sizeof *v);
            v->iov_base = (void *) i;
            v->iov_len = i * i;
            // Default insert, which allocates internal rb_nodes for you.
            printf("[rb_tree_insert] insert %p with base %p len %d\r\n",
                    v,
                    v->iov_base,
                    v->iov_len
            );
            rb_tree_insert(tree, v);
        }

        // To f
        struct iovec *f = rb_tree_find(tree,
                & (struct iovec) { .iov_base = (void *) 7, .iov_len = 0 }
        );
        if (f) {
            printf("[rb_tree_find] found iovec %p(.iov_base = %p, .iov_len = %zu)\n", f, f->iov_base, f->iov_len);
        } else {
            printf("[rb_tree_find] iov_len 9 not found\n");
        }

        printf("[rb_tree_test] testing...\r\n");
        rb_tree_test(tree, f);

        f = rb_tree_find(tree,
                & (struct iovec) { .iov_base = (void *) 7, .iov_len = 10 }
        );
        if (f) {
            printf("[rb_tree_find] found iovec %p(.iov_base = %p, .iov_len = %zu)\n", f, f->iov_base, f->iov_len);
        } else {
            printf("[rb_tree_find] iov_len 10 not found\n");
        }

        printf("[rb_tree_size] is %d\r\n", rb_tree_size(tree));

        // Dealloc call can take optional parameter to notify on each node
        // being deleted so you can free the node and/or your object:
        rb_tree_dealloc(tree, NULL);
    }
}

