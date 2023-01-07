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

#include <FreeRTOS.h>
#include "utils_rbtree.h"

// rb_node

struct rb_node * rb_node_alloc () 
{
    return pvPortMalloc(sizeof(struct rb_node));
}

struct rb_node * rb_node_init (struct rb_node *self, void *value) 
{
    if (self) {
        self->red = 1;
        self->link[0] = self->link[1] = NULL;
        self->value = value;
    }
    return self;
}

struct rb_node * rb_node_create (void *value) 
{
    return rb_node_init(rb_node_alloc(), value);
}

void rb_node_dealloc (struct rb_node *self) 
{
    if (self) {
        vPortFree(self);
    }
}

static int rb_node_is_red (const struct rb_node *self) 
{
    return self ? self->red : 0;
}

static struct rb_node * rb_node_rotate (struct rb_node *self, int dir) 
{
    struct rb_node *result = NULL;

    if (self) {
        result = self->link[!dir];
        self->link[!dir] = result->link[dir];
        result->link[dir] = self;
        self->red = 1;
        result->red = 0;
    }
    return result;
}

static struct rb_node * rb_node_rotate2 (struct rb_node *self, int dir) 
{
    struct rb_node *result = NULL;

    if (self) {
        self->link[!dir] = rb_node_rotate(self->link[!dir], !dir);
        result = rb_node_rotate(self, dir);
    }
    return result;
}

// rb_tree - default callbacks
int rb_tree_node_cmp_ptr_cb (struct rb_tree *self, struct rb_node *a, struct rb_node *b) 
{
    return (a->value > b->value) - (a->value < b->value);
}

void rb_tree_node_dealloc_cb (struct rb_tree *self, struct rb_node *node) 
{
    if (self) {
        if (node) {
            rb_node_dealloc(node);
        }
    }
}

// rb_tree
struct rb_tree * rb_tree_alloc () 
{
    return pvPortMalloc(sizeof(struct rb_tree));
}

struct rb_tree * rb_tree_init (struct rb_tree *self, rb_tree_node_cmp_f node_cmp_cb) 
{
    if (self) {
        self->root = NULL;
        self->size = 0;
        self->cmp = node_cmp_cb ? node_cmp_cb : rb_tree_node_cmp_ptr_cb;
    }

    return self;
}

struct rb_tree * rb_tree_create (rb_tree_node_cmp_f node_cb) 
{
    return rb_tree_init(rb_tree_alloc(), node_cb);
}

void rb_tree_dealloc(struct rb_tree *self, rb_tree_node_f node_cb) 
{
    if (self) {
        if (node_cb) {
            struct rb_node *node = self->root;
            struct rb_node *save = NULL;
            
            // Rotate away the left links so that
            // we can treat this like the destruction
            // of a linked list
            while (node) {
                if (node->link[0] == NULL) {

                    // No left links, just kill the node and move on
                    save = node->link[1];
                    node_cb(self, node);
                    node = NULL;
                } else {
                    
                    // Rotate away the left link and check again
                    save = node->link[0];
                    node->link[0] = save->link[1];
                    save->link[1] = node;
                }
                node = save;
            }
        }
        vPortFree(self);
    }
}

int rb_tree_test(struct rb_tree *self, struct rb_node *root) 
{
    int lh, rh;
    
    if (NULL == root) {
        return 1;
    } else {
        struct rb_node *ln = root->link[0];
        struct rb_node *rn = root->link[1];
        
        /* Consecutive red links */
        if (rb_node_is_red(root)) {
            if (rb_node_is_red(ln) || rb_node_is_red(rn)) {
                printf("Red violation");
                return 0;
            }
        }
        
        lh = rb_tree_test(self, ln);
        rh = rb_tree_test(self, rn);
        
        /* Invalid binary search tree */
        if ( ( ln != NULL && self->cmp(self, ln, root) >= 0 )
            || ( rn != NULL && self->cmp(self, rn, root) <= 0))
        {
            puts ( "Binary tree violation" );
            return 0;
        }
        
        /* Black height mismatch */
        if ( lh != 0 && rh != 0 && lh != rh ) {
            puts ( "Black violation" );
            return 0;
        }
        
        /* Only count black links */
        if ( lh != 0 && rh != 0 )
            return rb_node_is_red ( root ) ? lh : lh + 1;
        else
            return 0;
    }
}

void * rb_tree_find(struct rb_tree *self, void *value) 
{
    void *result = NULL;

    if (self) {
        struct rb_node node = { .value = value };
        struct rb_node *it = self->root;
        int cmp = 0;
        while (it) {
            if ((cmp = self->cmp(self, it, &node))) {

                // If the tree supports duplicates, they should be
                // chained to the right subtree for this to work
                it = it->link[cmp < 0];
            } else {
                break;
            }
        }
        result = it ? it->value : NULL;
    }
    return result;
}

// Creates (malloc'ates) 
int rb_tree_insert(struct rb_tree *self, void *value) 
{
    struct rb_node *node;

    if (NULL == self) {
        return 0;
    }

    node = rb_node_create(value);

    if (NULL == node) {
        return 0;
    }

    return rb_tree_insert_node(self, node);
}

// Returns 1 on success, 0 otherwise.
int rb_tree_insert_node (struct rb_tree *self, struct rb_node *node) 
{
    if (self && node) {
        if (self->root == NULL) {
            self->root = node;
        } else {
            struct rb_node head = { 0 }; // False tree root
            struct rb_node *g, *t;       // Grandparent & parent
            struct rb_node *p, *q;       // Iterator & parent
            int dir = 0, last = 0;

            // Set up our helpers
            t = &head;
            g = p = NULL;
            q = t->link[1] = self->root;

            // Search down the tree for a place to insert
            while (1) {
                if (q == NULL) {

                    // Insert node at the first null link.
                    p->link[dir] = q = node;
                } else if (rb_node_is_red(q->link[0]) && rb_node_is_red(q->link[1])) {
                
                    // Simple red violation: color flip
                    q->red = 1;
                    q->link[0]->red = 0;
                    q->link[1]->red = 0;
                }

                if (rb_node_is_red(q) && rb_node_is_red(p)) {

                    // Hard red violation: rotations necessary
                    int dir2 = t->link[1] == g;
                    if (q == p->link[last]) {
                        t->link[dir2] = rb_node_rotate(g, !last);
                    } else {
                        t->link[dir2] = rb_node_rotate2(g, !last);
                    }
                }
          
                // Stop working if we inserted a node. This
                // check also disallows duplicates in the tree
                if (self->cmp(self, q, node) == 0) {
                    break;
                }

                last = dir;
                dir = self->cmp(self, q, node) < 0;

                // Move the helpers down
                if (g != NULL) {
                    t = g;
                }

                g = p, p = q;
                q = q->link[dir];
            }

            // Update the root (it may be different)
            self->root = head.link[1];
        }

        // Make the root black for simplified logic
        self->root->red = 0;
        ++self->size;
    } else {
        return 0;
    }
    
    return 1;
}

// Returns 1 if the value was removed, 0 otherwise. Optional node callback
// can be provided to dealloc node and/or user data. Use rb_tree_node_dealloc
// default callback to deallocate node created by rb_tree_insert(...).
int rb_tree_remove_with_cb (struct rb_tree *self, void *value, rb_tree_node_f node_cb) 
{
    if (self->root != NULL) {
        struct rb_node head = {0}; // False tree root
        struct rb_node node = { .value = value }; // Value wrapper node
        struct rb_node *q, *p, *g; // Helpers
        struct rb_node *f = NULL;  // Found item
        int dir = 1;

        // Set up our helpers
        q = &head;
        g = p = NULL;
        q->link[1] = self->root;
    
        // Search and push a red node down
        // to fix red violations as we go
        while (q->link[dir] != NULL) {
            int last = dir;

            // Move the helpers down
            g = p, p = q;
            q = q->link[dir];
            dir = self->cmp(self, q, &node) < 0;
      
            // Save the node with matching value and keep
            // going; we'll do removal tasks at the end
            if (self->cmp(self, q, &node) == 0) {
                f = q;
            }

            // Push the red node down with rotations and color flips
            if (!rb_node_is_red(q) && !rb_node_is_red(q->link[dir])) {
                if (rb_node_is_red(q->link[!dir])) {
                    p = p->link[last] = rb_node_rotate(q, dir);
                } else if (!rb_node_is_red(q->link[!dir])) {
                    struct rb_node *s = p->link[!last];
                    if (s) {
                        if (!rb_node_is_red(s->link[!last]) && !rb_node_is_red(s->link[last])) {

                            // Color flip
                            p->red = 0;
                            s->red = 1;
                            q->red = 1;
                        } else {
                            int dir2 = g->link[1] == p;
                            if (rb_node_is_red(s->link[last])) {
                                g->link[dir2] = rb_node_rotate2(p, last);
                            } else if (rb_node_is_red(s->link[!last])) {
                                g->link[dir2] = rb_node_rotate(p, last);
                            }
                            
                            // Ensure correct coloring
                            q->red = g->link[dir2]->red = 1;
                            g->link[dir2]->link[0]->red = 0;
                            g->link[dir2]->link[1]->red = 0;
                        }
                    }
                }
            }
        }

        // Replace and remove the saved node
        if (f) {
            void *tmp = f->value;
            f->value = q->value;
            q->value = tmp;
            
            p->link[p->link[1] == q] = q->link[q->link[0] == NULL];
            
            if (node_cb) {
                node_cb(self, q);
            }
            q = NULL;
        }

        // Update the root (it may be different)
        self->root = head.link[1];

        // Make the root black for simplified logic
        if (self->root != NULL) {
            self->root->red = 0;
        }

        --self->size;
    }
    return 1;
}

int rb_tree_remove (struct rb_tree *self, void *value) 
{
    int result = 0;

    if (self) {
        result = rb_tree_remove_with_cb(self, value, rb_tree_node_dealloc_cb);
    }
    return result;
}

size_t rb_tree_size (struct rb_tree *self) 
{
    size_t result = 0;

    if (self) {
        result = self->size;
    }
    return result;
}

// rb_iter
struct rb_iter * rb_iter_alloc () 
{
    return pvPortMalloc(sizeof(struct rb_iter));
}

struct rb_iter * rb_iter_init (struct rb_iter *self) 
{
    if (self) {
        self->tree = NULL;
        self->node = NULL;
        self->top = 0;
    }
    return self;
}

struct rb_iter * rb_iter_create () 
{
    return rb_iter_init(rb_iter_alloc());
}

void rb_iter_dealloc (struct rb_iter *self) 
{
    if (self) {
        vPortFree(self);
    }
}

// Internal function, init traversal object, dir determines whether
// to begin traversal at the smallest or largest valued node.
static void * rb_iter_start (struct rb_iter *self, struct rb_tree *tree, int dir) 
{
    void *result = NULL;

    if (self) {
        self->tree = tree;
        self->node = tree->root;
        self->top = 0;

        // Save the path for later selfersal
        if (self->node != NULL) {
            while (self->node->link[dir] != NULL) {
                self->path[self->top++] = self->node;
                self->node = self->node->link[dir];
            }
        }
        result = self->node == NULL ? NULL : self->node->value;
    }

    return result;
}

// Traverse a red black tree in the user-specified direction (0 asc, 1 desc)
static void * rb_iter_move(struct rb_iter *self, int dir) 
{
    if (self->node->link[dir] != NULL) {
        // Continue down this branch
        self->path[self->top++] = self->node;
        self->node = self->node->link[dir];
        while ( self->node->link[!dir] != NULL ) {
            self->path[self->top++] = self->node;
            self->node = self->node->link[!dir];
        }
    } else {
        // Move to the next branch
        struct rb_node *last = NULL;
        do {
            if (self->top == 0) {
                self->node = NULL;
                break;
            }
            last = self->node;
            self->node = self->path[--self->top];
        } while (last == self->node->link[dir]);
    }
    return self->node == NULL ? NULL : self->node->value;
}

void *rb_iter_first(struct rb_iter *self, struct rb_tree *tree) 
{
    return rb_iter_start(self, tree, 0);
}

void * rb_iter_last(struct rb_iter *self, struct rb_tree *tree) 
{
    return rb_iter_start(self, tree, 1);
}

void * rb_iter_next(struct rb_iter *self)
{
    return rb_iter_move(self, 1);
}

void * rb_iter_prev(struct rb_iter *self)
{
    return rb_iter_move(self, 0);
}
