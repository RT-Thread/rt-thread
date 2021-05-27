/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-03-25     quanzhao     the first version
 */
#ifndef __MMU_H_
#define __MMU_H_

#include <rtthread.h>

#define DESC_SEC       (0x2)
#define MEMWBWA        ((1<<12)|(3<<2))     /* write back, write allocate */
#define MEMWB          (3<<2)  /* write back, no write allocate */
#define MEMWT          (2<<2)  /* write through, no write allocate */
#define SHAREDEVICE    (1<<2)  /* shared device */
#define STRONGORDER    (0<<2)  /* strong ordered */
#define XN             (1<<4)  /* eXecute Never */
#define AP_RW          (3<<10) /* supervisor=RW, user=RW */
#define AP_RO          (2<<10) /* supervisor=RW, user=RO */
#define SHARED         (1<<16) /* shareable */

#define DOMAIN_FAULT   (0x0)
#define DOMAIN_CHK     (0x1)
#define DOMAIN_NOTCHK  (0x3)
#define DOMAIN0        (0x0<<5)
#define DOMAIN1        (0x1<<5)

#define DOMAIN0_ATTR   (DOMAIN_CHK<<0)
#define DOMAIN1_ATTR   (DOMAIN_FAULT<<2)

/* device mapping type */
#define DEVICE_MEM     (SHARED|AP_RW|DOMAIN0|SHAREDEVICE|DESC_SEC|XN)
/* normal memory mapping type */
#define NORMAL_MEM     (SHARED|AP_RW|DOMAIN0|MEMWBWA|DESC_SEC)

struct mem_desc
{
    rt_uint32_t vaddr_start;
    rt_uint32_t vaddr_end;
    rt_uint32_t paddr_start;
    rt_uint32_t attr;
};


#endif
