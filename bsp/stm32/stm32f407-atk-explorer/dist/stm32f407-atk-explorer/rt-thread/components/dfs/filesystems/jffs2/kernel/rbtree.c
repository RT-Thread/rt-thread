/*========================================================================
//
//      rbtree.c
//
//      Red Black tree implementation
//
//========================================================================
// ####ECOSGPLCOPYRIGHTBEGIN####                                            
// -------------------------------------------                              
// This file is part of eCos, the Embedded Configurable Operating System.   
// Copyright (C) 1998, 1999, 2000, 2001, 2002, 2003 Free Software Foundation, Inc.
//
// eCos is free software; you can redistribute it and/or modify it under    
// the terms of the GNU General Public License as published by the Free     
// Software Foundation; either version 2 or (at your option) any later      
// version.                                                                 
//
// eCos is distributed in the hope that it will be useful, but WITHOUT      
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or    
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License    
// for more details.                                                        
//
// You should have received a copy of the GNU General Public License        
// along with eCos; if not, write to the Free Software Foundation, Inc.,    
// 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.            
//
// As a special exception, if other files instantiate templates or use      
// macros or inline functions from this file, or you compile this file      
// and link it with other works to produce a work based on this file,       
// this file does not by itself cause the resulting work to be covered by   
// the GNU General Public License. However the source code for this file    
// must still be made available in accordance with section (3) of the GNU   
// General Public License v2.                                               
//
// This exception does not invalidate any other reasons why a work based    
// on this file might be covered by the GNU General Public License.         
// -------------------------------------------                              
// ####ECOSGPLCOPYRIGHTEND####                                              
//========================================================================
//#####DESCRIPTIONBEGIN####
//
// Author(s):     Niels Provos/OpenBSD
// Contributors:  dwmw2
// Date:          2003-01-21
// Purpose:       This file provides an implementation of red-black trees.
// Description:   Derived from OpenBSD src/sys/sys/tree.h
// Usage:         
//
//####DESCRIPTIONEND####
//
//======================================================================
*/

/*	$OpenBSD: tree.h,v 1.7 2002/10/17 21:51:54 art Exp $	*/
/*
 * Copyright 2002 Niels Provos <provos@citi.umich.edu>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* Fields renamed to match Linux ones. */
#include <linux/rbtree.h>


#define RB_HEAD(head)		(head)->rb_node
#define RB_LEFT(elm)		(elm)->rb_left
#define RB_RIGHT(elm)		(elm)->rb_right
#define RB_PARENT(elm)		(elm)->rb_parent
#define RB_COLOR(elm)		(elm)->rb_color


#define RB_SET(elm, parent) do {				\
	RB_PARENT(elm) = parent;				\
	RB_LEFT(elm) = RB_RIGHT(elm) = NULL;	\
	RB_COLOR(elm) = RB_RED;				\
} while (0)

#define RB_SET_BLACKRED(black, red) do {			\
	RB_COLOR(black) = RB_BLACK;				\
	RB_COLOR(red) = RB_RED;					\
} while (0)

#ifndef RB_AUGMENT
#define RB_AUGMENT(x)
#endif

#define RB_ROTATE_LEFT(head, elm, tmp) do {			\
	(tmp) = RB_RIGHT(elm);					\
	if ((RB_RIGHT(elm) = RB_LEFT(tmp))) {			\
		RB_PARENT(RB_LEFT(tmp)) = (elm);		\
	}							\
	RB_AUGMENT(elm);					\
	if ((RB_PARENT(tmp) = RB_PARENT(elm))) {		\
		if ((elm) == RB_LEFT(RB_PARENT(elm)))		\
			RB_LEFT(RB_PARENT(elm)) = (tmp);	\
		else						\
			RB_RIGHT(RB_PARENT(elm)) = (tmp);	\
	} else							\
		(head)->rb_node = (tmp);			\
	RB_LEFT(tmp) = (elm);					\
	RB_PARENT(elm) = (tmp);					\
	RB_AUGMENT(tmp);					\
	if ((RB_PARENT(tmp)))					\
		RB_AUGMENT(RB_PARENT(tmp));			\
} while (0)

#define RB_ROTATE_RIGHT(head, elm, tmp) do {			\
	(tmp) = RB_LEFT(elm);					\
	if ((RB_LEFT(elm) = RB_RIGHT(tmp))) {			\
		RB_PARENT(RB_RIGHT(tmp)) = (elm);		\
	}							\
	RB_AUGMENT(elm);					\
	if ((RB_PARENT(tmp) = RB_PARENT(elm))) {		\
		if ((elm) == RB_LEFT(RB_PARENT(elm)))		\
			RB_LEFT(RB_PARENT(elm)) = (tmp);	\
		else						\
			RB_RIGHT(RB_PARENT(elm)) = (tmp);	\
	} else							\
		(head)->rb_node = (tmp);			\
	RB_RIGHT(tmp) = (elm);					\
	RB_PARENT(elm) = (tmp);					\
	RB_AUGMENT(tmp);					\
	if ((RB_PARENT(tmp)))					\
		RB_AUGMENT(RB_PARENT(tmp));			\
} while(0)

/* Note args swapped to match Linux */
void rb_insert_color(struct rb_node *elm, struct rb_root *head)
{
	struct rb_node *parent, *gparent, *tmp;
	while ((parent = RB_PARENT(elm)) &&
	    RB_COLOR(parent) == RB_RED) {
		gparent = RB_PARENT(parent);
		if (parent == RB_LEFT(gparent)) {
			tmp = RB_RIGHT(gparent);
			if (tmp && RB_COLOR(tmp) == RB_RED) {
				RB_COLOR(tmp) = RB_BLACK;
				RB_SET_BLACKRED(parent, gparent);
				elm = gparent;
				continue;
			}
			if (RB_RIGHT(parent) == elm) {
				RB_ROTATE_LEFT(head, parent, tmp);
				tmp = parent;
				parent = elm;
				elm = tmp;
			}
			RB_SET_BLACKRED(parent, gparent);
			RB_ROTATE_RIGHT(head, gparent, tmp);
		} else {
			tmp = RB_LEFT(gparent);
			if (tmp && RB_COLOR(tmp) == RB_RED) {
				RB_COLOR(tmp) = RB_BLACK;
				RB_SET_BLACKRED(parent, gparent);
				elm = gparent;
				continue;
			}
			if (RB_LEFT(parent) == elm) {
				RB_ROTATE_RIGHT(head, parent, tmp);
				tmp = parent;
				parent = elm;
				elm = tmp;
			}
			RB_SET_BLACKRED(parent, gparent);
			RB_ROTATE_LEFT(head, gparent, tmp);
		}
	}
	RB_COLOR(head->rb_node) = RB_BLACK;
}


static void rb_remove_color(struct rb_root *head, struct rb_node *parent,
			    struct rb_node *elm)
{
	struct rb_node *tmp;
	while ((elm == NULL || RB_COLOR(elm) == RB_BLACK) &&
	    elm != RB_HEAD(head)) {
		if (RB_LEFT(parent) == elm) {
			tmp = RB_RIGHT(parent);
			if (RB_COLOR(tmp) == RB_RED) {
				RB_SET_BLACKRED(tmp, parent);
				RB_ROTATE_LEFT(head, parent, tmp);
				tmp = RB_RIGHT(parent);
			}
			if ((RB_LEFT(tmp) == NULL ||
			    RB_COLOR(RB_LEFT(tmp)) == RB_BLACK) &&
			    (RB_RIGHT(tmp) == NULL ||
			    RB_COLOR(RB_RIGHT(tmp)) == RB_BLACK)) {
				RB_COLOR(tmp) = RB_RED;
				elm = parent;
				parent = RB_PARENT(elm);
			} else {
				if (RB_RIGHT(tmp) == NULL ||
				    RB_COLOR(RB_RIGHT(tmp)) == RB_BLACK) {
					struct rb_node *oleft;
					if ((oleft = RB_LEFT(tmp)))
						RB_COLOR(oleft) = RB_BLACK;
					RB_COLOR(tmp) = RB_RED;
					RB_ROTATE_RIGHT(head, tmp, oleft);
					tmp = RB_RIGHT(parent);
				}
				RB_COLOR(tmp) = RB_COLOR(parent);
				RB_COLOR(parent) = RB_BLACK;
				if (RB_RIGHT(tmp))
					RB_COLOR(RB_RIGHT(tmp)) = RB_BLACK;
				RB_ROTATE_LEFT(head, parent, tmp);
				elm = RB_HEAD(head);
				break;
			}
		} else {
			tmp = RB_LEFT(parent);
			if (RB_COLOR(tmp) == RB_RED) {
				RB_SET_BLACKRED(tmp, parent);
				RB_ROTATE_RIGHT(head, parent, tmp);
				tmp = RB_LEFT(parent);
			}
			if ((RB_LEFT(tmp) == NULL ||
			    RB_COLOR(RB_LEFT(tmp)) == RB_BLACK) &&
			    (RB_RIGHT(tmp) == NULL ||
			    RB_COLOR(RB_RIGHT(tmp)) == RB_BLACK)) {
				RB_COLOR(tmp) = RB_RED;
				elm = parent;
				parent = RB_PARENT(elm);
			} else {
				if (RB_LEFT(tmp) == NULL ||
				    RB_COLOR(RB_LEFT(tmp)) == RB_BLACK) {
					struct rb_node *oright;
					if ((oright = RB_RIGHT(tmp)))
						RB_COLOR(oright) = RB_BLACK;
					RB_COLOR(tmp) = RB_RED;
					RB_ROTATE_LEFT(head, tmp, oright);
					tmp = RB_LEFT(parent);
				}
				RB_COLOR(tmp) = RB_COLOR(parent);
				RB_COLOR(parent) = RB_BLACK;
				if (RB_LEFT(tmp))
					RB_COLOR(RB_LEFT(tmp)) = RB_BLACK;
				RB_ROTATE_RIGHT(head, parent, tmp);
				elm = RB_HEAD(head);
				break;
			}
		}
	}
	if (elm)
		RB_COLOR(elm) = RB_BLACK;
}

/* Note name changed. Guess why :) */
void rb_erase(struct rb_node *elm, struct rb_root *head)
{
	struct rb_node *child, *parent, *old = elm;
	int color;
	if (RB_LEFT(elm) == NULL)
		child = RB_RIGHT(elm);
	else if (RB_RIGHT(elm) == NULL)
		child = RB_LEFT(elm);
	else {
		struct rb_node *left;
		elm = RB_RIGHT(elm);
		while ((left = RB_LEFT(elm)))
			elm = left;
		child = RB_RIGHT(elm);
		parent = RB_PARENT(elm);
		color = RB_COLOR(elm);
		if (child)
			RB_PARENT(child) = parent;
		if (parent) {
			if (RB_LEFT(parent) == elm)
				RB_LEFT(parent) = child;
			else
				RB_RIGHT(parent) = child;
			RB_AUGMENT(parent);
		} else
			RB_HEAD(head) = child;
		if (RB_PARENT(elm) == old)
			parent = elm;
		*(elm) = *(old);
		if (RB_PARENT(old)) {
			if (RB_LEFT(RB_PARENT(old)) == old)
				RB_LEFT(RB_PARENT(old)) = elm;
			else
				RB_RIGHT(RB_PARENT(old)) = elm;
			RB_AUGMENT(RB_PARENT(old));
		} else
			RB_HEAD(head) = elm;
		RB_PARENT(RB_LEFT(old)) = elm;
		if (RB_RIGHT(old))
			RB_PARENT(RB_RIGHT(old)) = elm;
		if (parent) {
			left = parent;
			do {
				RB_AUGMENT(left);
			} while ((left = RB_PARENT(left)));
		}
		goto color;
	}
	parent = RB_PARENT(elm);
	color = RB_COLOR(elm);
	if (child)
		RB_PARENT(child) = parent;
	if (parent) {
		if (RB_LEFT(parent) == elm)
			RB_LEFT(parent) = child;
		else
			RB_RIGHT(parent) = child;
		RB_AUGMENT(parent);
	} else
		RB_HEAD(head) = child;
color:
	if (color == RB_BLACK)
		rb_remove_color(head, parent, child);
}

struct rb_node *rb_next(struct rb_node *elm)
{
	if (RB_RIGHT(elm)) {
		elm = RB_RIGHT(elm);
		while (RB_LEFT(elm))
			elm = RB_LEFT(elm);
	} else {
		if (RB_PARENT(elm) &&
		    (elm == RB_LEFT(RB_PARENT(elm))))
			elm = RB_PARENT(elm);
		else {
			while (RB_PARENT(elm) &&
			    (elm == RB_RIGHT(RB_PARENT(elm))))
				elm = RB_PARENT(elm);
			elm = RB_PARENT(elm);
		}
	}
	return (elm);
}

struct rb_node *rb_prev(struct rb_node *elm)
{
	if (RB_LEFT(elm)) {
		elm = RB_LEFT(elm);
		while (RB_RIGHT(elm))
			elm = RB_RIGHT(elm);
	} else {
		if (RB_PARENT(elm) &&
		    (elm == RB_RIGHT(RB_PARENT(elm))))
			elm = RB_PARENT(elm);
		else {
			while (RB_PARENT(elm) &&
			    (elm == RB_LEFT(RB_PARENT(elm))))
				elm = RB_PARENT(elm);
			elm = RB_PARENT(elm);
		}
	}
	return (elm);
}

/* These ones are lifted from Linux -- but that's OK because I
   wrote them. dwmw2. */
struct rb_node *rb_first(struct rb_root *root)
{
        struct rb_node  *n;

        n = root->rb_node;
        if (!n)
                return 0;
        while (n->rb_left)
                n = n->rb_left;
        return n;
}

void rb_replace_node(struct rb_node *victim, struct rb_node *new,
                     struct rb_root *root)
{
        struct rb_node *parent = victim->rb_parent;

        /* Set the surrounding nodes to point to the replacement */
        if (parent) {
                if (victim == parent->rb_left)
                        parent->rb_left = new;
                else
                        parent->rb_right = new;
        } else {
                root->rb_node = new;
        }
        if (victim->rb_left)
                victim->rb_left->rb_parent = new;
        if (victim->rb_right)
                victim->rb_right->rb_parent = new;

        /* Copy the pointers/colour from the victim to the replacement */
        *new = *victim;
}
