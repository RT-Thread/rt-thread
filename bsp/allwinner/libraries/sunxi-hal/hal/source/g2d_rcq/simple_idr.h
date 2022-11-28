/*
 * simple_idr.h
 *
 * Copyright (c) 2007-2019 Allwinnertech Co., Ltd.
 * 
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <hal_sem.h>

#ifndef _MALI_IDR_H
#define _MALI_IDR_H
#define IDR_BIT 8
#define IDR_SIZE (1<<8)
#define IDR32_MASK 0xffffffff
#define NO_ID 0

struct id_layer {
    int num_layer;
    struct id_layer *layer[IDR_SIZE];
    int bitmap[IDR_SIZE/32];//full will set
    struct id_layer *pre;
    struct id_layer *next;
};

struct id_dir {
    hal_sem_t lock;
    struct id_layer  *top;
    struct id_layer *lu_cache[4];
    int lu_id;
    int cur_max_level;
    int status;// -1 is destroyed, 0 is normal no visitting, 1 is now visitting...
    struct id_layer *head;
};

int id_alloc(struct id_dir *dir, void *value);


void id_free(struct id_dir *dir, int id);

void* id_get(struct id_dir *dir, int id);

struct id_dir* id_creat(void);

void id_destroyed(struct id_dir *dir);

#endif
