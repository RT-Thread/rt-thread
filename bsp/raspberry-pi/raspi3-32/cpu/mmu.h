#ifndef MMU_H__
#define MMU_H__
#include <rtthread.h>
#include <rthw.h>
#include <board.h>
#include "cp15.h"

#define DESC_SEC       (0x2)
#define CB             (3 << 2)  //cache_on, write_back
#define CNB            (2 << 2)  //cache_on, write_through
#define NCB            (1 << 2)  //cache_off,WR_BUF on
#define NCNB           (0 << 2)  //cache_off,WR_BUF off
#define AP_RW          (3 << 10) //supervisor=RW, user=RW
#define AP_RO          (2 << 10) //supervisor=RW, user=RO
#define XN             (1 << 4)  // eXecute Never
#define SHARED         (1 << 16) /* shareable */
#define SHAREDEVICE    (1 << 2)  /* shared device */
#define STRONGORDER    (0 << 2)  /* strong ordered */
#define MEMWBWA        ((1 << 12) | (3 << 2))     /* write back, write allocate */

#define DOMAIN_FAULT   (0x0)
#define DOMAIN_CHK     (0x1)
#define DOMAIN_NOTCHK  (0x3)
#define DOMAIN0        (0x0 << 5)
#define DOMAIN1        (0x1 << 5)

#define DOMAIN0_ATTR   (DOMAIN_CHK << 0)
#define DOMAIN1_ATTR   (DOMAIN_FAULT << 2)

/* Read/Write, cache, write back */
#define RW_CB          (AP_RW | DOMAIN0 | CB | DESC_SEC)
/* Read/Write, cache, write through */
#define RW_CNB         (AP_RW | DOMAIN0 | CNB | DESC_SEC)
/* Read/Write without cache and write buffer */
#define RW_NCNB        (AP_RW | DOMAIN0 | NCNB | DESC_SEC)
/* Read/Write without cache and write buffer, no execute */
#define RW_NCNBXN      (AP_RW | DOMAIN0 | NCNB | DESC_SEC | XN)
/* Read/Write without cache and write buffer */
#define RW_FAULT       (AP_RW | DOMAIN1 | NCNB | DESC_SEC)

/* device mapping type */
#define DEVICE_MEM     (SHARED | SHAREDEVICE | RW_NCNBXN)
/* normal memory mapping type */
#define NORMAL_MEM     (SHARED | AP_RW | DOMAIN0 | MEMWBWA | DESC_SEC)
#define STRONG_ORDER_MEM (SHARED | AP_RO | XN | DESC_SEC)
#define BUS_ADDRESS(phys)	(((phys) & ~0xC0000000)  |  0xC0000000)

void rt_hw_change_mmu_table(rt_uint32_t vaddrStart,
                      rt_uint32_t size,
                      rt_uint32_t paddrStart, rt_uint32_t attr);
#endif
