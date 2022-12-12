/*
 * simple_idr.c
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


//not apply it in the IRQ, a simple idr from linux
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "g2d_bsp.h"
#include "simple_idr.h"

static struct id_layer** find_empty_slot(struct id_layer *up_layer, int *id_index)
{
    //first  right  empty  0~31
    int i = 0, start = 0, id = 0;

    for (i = 0; i < IDR_SIZE/32; i++)
        if(up_layer->bitmap[i] != IDR32_MASK)
            break;
    if (i == IDR_SIZE/32) {
        *id_index = NO_ID;
        return NULL;
    }

    if (up_layer->bitmap[i] == 0)
        goto cal;
    id = ~up_layer->bitmap[i];
    // 0~31 bit
    if (!(id&0x0000ffff)) {
        start +=16;
        id >>= 16;
    }
    if (!(id&0x00ff)) {
        start += 8;
        id >>= 8;
    }
    if (!(id&0x0f)) {
        start += 4;
        id >>= 4;
    }
    if (!(id&0x3)) {
        start += 2;
        id >>= 2;
    }
    if (!(id&0x1)) {
        start += 1;
        id >>= 1;
    }
cal:
    *id_index = i*32+start;

    return &up_layer->layer[*id_index];
}

int id_alloc(struct id_dir *dir, void *value)
{
    int id = NO_ID, id_index = NO_ID;
    int i = 0;
    int curr_lvl;
    struct id_layer **cur = NULL, *tmp = NULL;

    if (dir == NULL || dir->status == -1)
        return NO_ID;

    hal_sem_wait(dir->lock);

    if (dir->status == -1)
        goto out;
    dir->status = 1;
    if (dir->lu_cache[0] != NULL) {
        tmp = dir->lu_cache[0];
        id = dir->lu_id;
        cur = find_empty_slot(tmp, &id_index);
        id = (id&(~0xff)) + id_index;
    }else{
        //add a new top
        if (dir->top == NULL || find_empty_slot(dir->top, &id_index) == NULL) {
            if (dir->top && dir->cur_max_level > 2) {
                G2D_INFO_MSG("a full idr,we only support 32bit\n");
                goto out;
            }
            tmp = (struct id_layer*)hal_malloc(sizeof(struct id_layer));
	    memset(tmp, 0, sizeof(struct id_layer));
            tmp->layer[0] = dir->top;
            tmp->bitmap[0] = 0x01;//0 is NO_ID
            tmp->num_layer = 1;
            dir->cur_max_level++;
            dir->top = tmp;
            if (dir->head) {
                dir->head->pre = tmp;
            }
            tmp->next = dir->head;
        }
        curr_lvl = dir->cur_max_level;
        for (cur= &dir->top; *cur != NULL; id <<= 8, id += id_index, curr_lvl--) {
            tmp = *cur;
            dir->lu_cache[curr_lvl] = tmp;
            cur = find_empty_slot(tmp, &id_index);
            if (curr_lvl > 0 && *cur == NULL) {
                //add a new child idr
                *cur = (struct id_layer*)hal_malloc(sizeof(struct id_layer));
                if (*cur == NULL) {
                    G2D_INFO_MSG("atomic alloc idr mem err.\n");
                    goto out;
                }
		memset(*cur, 0, sizeof(struct id_layer));
                tmp->num_layer++;
                (*cur)->next = dir->head;
                (*cur)->pre = NULL;
                dir->head = *cur;
            }
        }
    }

    dir->lu_id = id;
    *cur = (struct id_layer*)value;
    tmp->bitmap[id_index/32] |= 1 << (id_index%32);
    tmp->num_layer++;

    if (tmp->num_layer == IDR_SIZE) {
        dir->lu_cache[0] = NULL;
        for (i = 1; dir->lu_cache[i] != NULL && i < dir->cur_max_level; i++) {
            id_index = (id>>(8*i)) & 0xff;
            dir->lu_cache[i]->bitmap[id_index/32] |= 1 << (id_index%32);
            if (find_empty_slot(dir->lu_cache[i], &id_index) != NULL) {
                break;
            }
        }
    }
    dir->status = 0;
out:
    hal_sem_post(dir->lock);
   // printf("id_alloc:%d == %08x\n",id, value);

    return id;
}

void id_free(struct id_dir *dir, int id)
{
    struct id_layer* lu[4] = {NULL, NULL, NULL, NULL};

    int i = 0, id_index = 0;
    if (id>>((dir->cur_max_level+1)*8) || id == NO_ID
            || dir->top == NULL || dir->status == -1) {
        G2D_INFO_MSG("give a err id:%d, max:%ld\n", id, (1ul << ((dir->cur_max_level+1)* 8)) - 1);
        return;
    }

    hal_sem_wait(dir->lock);

    if (dir->status == -1)
        goto out;
    dir->status = 1;
    lu[dir->cur_max_level] = dir->top;
    for (i = dir->cur_max_level; i > 0; ) {
        id_index = (id>>(i*8)) & 0xff;
        i--;
        lu[i] = lu[i+1]->layer[id_index];
    }
    id_index = id&0xff;
    lu[0]->layer[id_index] = NULL;
    lu[0]->num_layer--;
    lu[0]->bitmap[id_index/32] &= ~(1<<(id_index % 32));

    for (i = 1; i <= dir->cur_max_level; i++) {
        id_index =  (id>>(i*8)) & 0xff;
        lu[i]->bitmap[id_index/32] &= ~(1<<(id_index % 32));

        if (lu[i-1]->num_layer == 0) {
            //top will not empty due to NO_ID, least 1 top layer.
            if (lu[i]->layer[id_index]->next != NULL)
                lu[i]->layer[id_index]->next->pre = lu[i]->layer[id_index]->pre;
            if (lu[i]->layer[id_index]->pre != NULL)
                lu[i]->layer[id_index]->pre->next = lu[i]->layer[id_index]->next;
            else
                dir->head = lu[i]->layer[id_index]->next;
            free(lu[i]->layer[id_index]);
            lu[i]->layer[id_index] = NULL;
            lu[i]->num_layer--;
        }
    }

//deal_top:
    while (dir->top->num_layer == 1 && dir->cur_max_level > 0
            && dir->top->layer[0] != NULL && dir->top->bitmap[0]^0x01) {
        lu[0] = dir->top;
        dir->top = lu[0]->layer[0];
        if (lu[0]->next != NULL)
            lu[0]->next->pre = lu[0]->pre;
        if (lu[0]->pre != NULL)
            lu[0]->pre->next = lu[0]->next;
        else
            dir->head = lu[0]->next;
        free(lu[0]);

        dir->cur_max_level--;
    }
    dir->status = 0;
out:
    hal_sem_post(dir->lock);
    //printf("leave id_free: %d \n", id);
}

void* id_get(struct id_dir *dir, int id)
{
    int id_index, i;
    struct id_layer *lu = NULL;

    if (dir == NULL || dir->top == NULL || dir->status == -1 || id == NO_ID)
        return NULL;
    //the atomic area , but not happen
    if (id>>((dir->cur_max_level+1)*8))
        return NULL;

    hal_sem_wait(dir->lock);
    if (dir->status == -1)
        goto out;
    dir->status = 1;
    lu = dir->top;
    for (i = dir->cur_max_level; i >= 0; i--) {
        id_index = (id>>(i*8)) & 0xff;
        lu = lu->layer[id_index];
        if (lu == NULL) {
            G2D_INFO_MSG("give a err id:%d\n", id);
            goto out;
        }
    }
    dir->status = 0;
    out:
    hal_sem_post(dir->lock);
	//printf("got id:%d=%08x\n",id,lu);
    return (void*)lu;
}

struct id_dir* id_creat(void)
{
    struct id_dir* idr;
    int i;
    idr = (struct id_dir*)hal_malloc(sizeof(struct id_dir));
    if(idr == NULL) {
        G2D_INFO_MSG("malloc idr err.\n");
        return NULL;
    }
    memset(idr, 0, sizeof(struct id_dir));
    idr->cur_max_level = -1;
    idr->lock = hal_sem_create(1);
    for(i = 0; i < 4; i++)
        idr->lu_cache[i] = NULL;
    idr->lu_id = 0;
    idr->head = NULL;
    idr->top = (struct id_layer*)hal_malloc(sizeof(struct id_layer));
    if (idr->top == NULL) {
        G2D_INFO_MSG("malloc id_layer err.\n");
        goto out;
    }
    memset(idr->top, 0, sizeof(struct id_layer));
    idr->top->bitmap[0] = 0x01; //0 is NO_ID
    idr->top->num_layer = 1;
    idr->cur_max_level = 0;
    idr->head = idr->top;
    idr->lu_cache[0] = idr->top;
out:
    return idr;
}

void id_destroyed(struct id_dir *dir)
{
    struct id_layer* free_id_layer;

    hal_sem_wait(dir->lock);
    dir->status = -1;
    hal_sem_post(dir->lock);

    while(dir->head != NULL) {
        free_id_layer = dir->head;
        dir->head = free_id_layer->next;
        free(free_id_layer);
    }
    free(dir);
}
