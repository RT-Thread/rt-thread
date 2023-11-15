#ifndef _IDR_H_
#define _IDR_H_

#include <rtdef.h>
#include <sys/types.h>
#include "avl.h"

struct idr {
    struct avl_root root;
    unsigned int base;
    unsigned int next;
};

void idr_init_base(struct idr*, unsigned int base);
void idr_init_new(struct idr*);
int idr_alloc_new(struct idr*, void* ptr, int start, int end);
int idr_alloc_u32(struct idr* idr, void* ptr, rt_uint32_t* nextid, unsigned long max);
void* idr_remove_new(struct idr*, unsigned long id);
void* idr_find_new(const struct idr*, unsigned long id);
void idr_destroy(struct idr*);

#endif
